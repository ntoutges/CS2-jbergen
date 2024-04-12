#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

#define USE_IMPROVED true

void buildArray(int[], int);
void bubbleSort(int[], int);
void selectionSort(int[], int);
void insertionSort(int[], int);
void betterMergeSort(int* array, int size);
void mergeSort(int[], int, int);
void merge(int[], int, int, int);

void printArray(int[], int);
void copyArray(int[], int[], int);

int main(int argc, char* argv[])
{
    const int arrSize = 100000;
    int array[arrSize];
    int bubbleArray[arrSize];
    int selectionArray[arrSize];
    int insertionArray[arrSize];
    int mergeArray[arrSize];

    cout << "Building array..." << endl;
    buildArray(array, arrSize);
    copyArray(array, bubbleArray, arrSize);

    auto start = chrono::system_clock::now();
    cout << "Bubble Sorting array..." << endl;
    // bubbleSort(bubbleArray, arrSize);
    auto end = chrono::system_clock::now();
    auto elapsed = end - start;
    cout << "Bubble Sort: " << elapsed.count() << '\n';


    start = chrono::system_clock::now();
    cout << "Selection Sorting array..." << endl;
    copyArray(array, selectionArray, arrSize);
    // selectionSort(selectionArray, arrSize);
    end = chrono::system_clock::now();
    elapsed = end - start;
    cout << "Selection Sort: " << elapsed.count() << '\n';

    start = chrono::system_clock::now();
    cout << "Insertion Sorting array..." << endl;
    copyArray(array, insertionArray, arrSize);
    // insertionSort(insertionArray, arrSize);
    end = chrono::system_clock::now();
    elapsed = end - start;
    cout << "Selection Sort: " << elapsed.count() << '\n';

    int l, r;
    l = 0;
    r = arrSize-1;

    start = chrono::system_clock::now();
    cout << "Merge Sorting array..." << endl;
    
    copyArray(array, mergeArray, arrSize);
    #if USE_IMPROVED
    betterMergeSort(mergeArray, arrSize);
    #else
    mergeSort(mergeArray, l, r);
    #endif

    end = chrono::system_clock::now();
    elapsed = end - start;
    cout << "Merge Sort: " << elapsed.count() << '\n';
    // printArray(bubbleArray, arrSize);
    // printArray(selectionArray, arrSize);
    // printArray(insertionArray, arrSize);
    // printArray(mergeArray, arrSize);
    return 0;
}

void copyArray(int origArray[], int newArray[], int arrSize)
{
    for(int i = 0; i < arrSize; i++)
    {
        newArray[i] = origArray[i];
    }
}

void printArray(int array[], int arrSize)
{
    for(int i = 0; i < arrSize; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void buildArray(int array[], int arrSize)
{
    // srand(time(0));
    for(int i = 0; i < arrSize; i++)
    {
        array[i] = rand();
    }
}

void merge(int array[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    int* L = (int*) malloc(sizeof(int) * n1);
    int* M = (int*) malloc(sizeof(int) * n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = array[p+i];
    }
    for (int j = 0; j < n1; j++)
    {
        M[j] = array[q + 1 + j];
    }

    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    while(i < n1 && j < n2)
    {
        if(L[i] <= M[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = M[j];
            j++;
        }
        k++;
    }
    while(i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }
    while(j < n2)
    {
        array[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int l, int r)
{
    
    if(l < r)
    {
        int m = l + (r - l - 1)/2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        
        merge(array, l, m, r);
    }
}

void betterMergeSort(int* array, int size) {
    int maxStep = size/2;
    int step = 1; // ideal size of a "chunk"
    int s1, s2; // actual size of chunk
    int s1i, s2i; // where located within chunk
    int* buffer = (int*) malloc(sizeof(int) * size);

    while (step <= maxStep) {
        for (int i = 0; i < size; i += 2*step) {
            // get size of next two chunks
            if (i + step < size) {
                s1 = step;
                if (i + 2*step < size) s2 = step;
                else s2 = size - step - i;
            }
            else break; // end of chunks; unable to merge something with nothing

            s1i = 0;
            s2i = 0;

            // fill/sort buffer 
            while (s1i < s1 && s2i < s2) {
                if (array[i + s1i] < array[i + s1 + s2i]) {
                    buffer[s1i + s2i] = array[i + s1i];
                    ++s1i;
                }
                else {
                    buffer[s1i + s2i] = array[i + s1 + s2i];
                    ++s2i;
                }
            }
            while (s1i < s1) {
                buffer[s1i+s2i] = array[i + s1i];
                ++s1i;
            }
            while (s2i < s2) {
                buffer[s1i+s2i] = array[i + s1 + s2i];
                ++s2i;
            }

            // shove buffer back into array
            for (int j = s1 + s2 - 1; j >= 0; j--) { array[i+j] = buffer[j]; }
        }
        step *= 2;
    }
    free(buffer);
}

void insertionSort(int array[], int arrSize)
{
    for(int i = 1; i < arrSize; i++)
    {
        int key = array[i];
        int j = i - 1;

        while(j >= 0 && array[j] > key)
        {
            array[j+1] = array[j];
            j = j - 1;
        }
        array[j+1] = key;
    }
}

void selectionSort(int array[], int arrSize)
{
    // bool swapped = false;
    int minimum;
    for(int i = 0; i < arrSize - 1; i++)
    {
        minimum = i;
        for(int j = i + 1; j < arrSize; j++)
        {
            if(array[j] < array[minimum])
            {
                minimum = j;
            }
        }
        if(minimum != i)
        {
            swap(array[minimum], array[i]);
        }
    }
}

void bubbleSort(int array[], int arrSize)
{
    bool swapped = false;
    for(int i = 0; i < arrSize; i++)
    {
        swapped = false;
        for(int j = 0; j < arrSize - 1 -i; j++)
        {
            if(array[j] > array[j+1])
            {
                swap(array[j], array[j+1]);
                swapped = true;
            }
        }
        if(!swapped) break;
    }
}
