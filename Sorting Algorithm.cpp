#include <chrono>
#include <iostream>
#include <random>

using namespace std;
using namespace std::chrono;
using std::chrono::system_clock;

bool check_sorted(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

void print_arr(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        if (i) cout << ", ";
        cout << arr[i];
    }
    cout << endl;
}

int* gen_data(int n, int seed = 0) {
    int* arr = new int[n];
    mt19937 rs(seed);
    uniform_int_distribution<int> dist(0, 1000000);

    for (int i = 0; i < n; i++) {
        arr[i] = dist(rs);
    }
    return arr;
}
int pow(int a, int b) {
    int tmp = 1;
    if (b == 0) {
        return 1;
    }
    for (int i = 1; i <= b; i++) {
        tmp = tmp * a;
    }
    return tmp;
}
void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;

}
//merge function for left, right sorted subarrays
void Merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int* L = new int[n1+1];
    int* R = new int[n2+1];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    L[n1] = INT32_MAX;
    R[n2] = INT32_MAX;

    int i = 0;
    int j = 0;
    for (int k = left; k <= right; k++) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
    }
    return;
}

// Recursion Function for merge sorting
void Merge_sorting(int* arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        Merge_sorting(arr, left, mid);
        Merge_sorting(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
    return;
}
//Max heapify function for Heap sort
void Max_heapify(int* arr, int i,int heap_size){
    
    int left = 2 * (i + 1) - 1;
    int right = 2 * (i + 1);
    int largest;
    if (left < heap_size && arr[left] > arr[i]){
        largest = left;
    }
    else {
        largest = i;
    }
    if (right < heap_size && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        Max_heapify(arr, largest, heap_size);
    }

}
// build complete max heap with Max_heapify function
void Build_Max_heap(int* arr, int n) {
    int heap_size = n;
    int last_parent_node = heap_size / 2 - 1;
    for (int i = last_parent_node; i >= 0; i--) {
        Max_heapify(arr, i,heap_size);
    }
}
//Partition function for quick sort
int Partition(int* arr, int left, int right) {
    int pivot = arr[right];
    int i = left-1;

    for (int j = left; j <right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}
// Randomized Partition 만들기 위한 random 분포 형성
random_device rd;
mt19937 gen(rd());
// Randomized Partition function for Randomized pivot quick sort
int Randomized_Partition(int* arr, int left, int right) {
    uniform_int_distribution<int> dis(left, right);
    int random_index = dis(gen);
    swap(arr[left], arr[random_index]);
    return Partition(arr, left, right);
}
//Recursive Function for Quick sort
void Quick_sorting(int* arr, int left, int right) {
    if (left < right) {
        int mid = Partition(arr, left, right);
        Quick_sorting(arr, left, mid - 1);
        Quick_sorting(arr, mid + 1, right);
    }
}
//Recursive Function for randomized pivot Quick sort
void Randomized_Quick_sorting(int* arr, int left, int right) {
    if (left < right) {
        int mid = Randomized_Partition(arr, left, right);
        Randomized_Quick_sorting(arr, left, mid - 1);
        Randomized_Quick_sorting(arr, mid + 1, right);
    }
}
//Recursive Function for stooge sort
void Stooge_sorting(int* arr, int left, int right) {
    if (arr[left] > arr[right]) {
        swap(arr[left], arr[right]);
    }
    int mid;
    if (right - left > 1) {
        mid = (right-left+1) / 3;
        Stooge_sorting(arr, left, right - mid);
        Stooge_sorting(arr, left+mid, right);
        Stooge_sorting(arr, left, right - mid);
    }
}
//Counting sort function with digit for radix sort
int* Counting_sort(int* arr, int n, int digit) {
    
    int* B = new int[n];
    int* C = new int[10];
    for (int i = 0; i < 10; i++) {
        C[i] = 0;
    }
    for (int j = 0; j < n; j++) {
        C[(arr[j] / pow(10, digit - 1)) % 10] += 1;
    }
    for (int i = 1; i < 10; i++) {
        C[i] = C[i] + C[i - 1];
    }
    for (int j = n - 1; j >=0; j--) {
        B[C[(arr[j] / pow(10, digit - 1)) % 10 ]-1] = arr[j];
        C[(arr[j] / pow(10, digit - 1)) % 10] -= 1;
    }
    return B;
}


//Insertion sort
int* insertion_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    int key;
    int i;
    for (int j = 1; j<n; j++) {
        key = sorted[j];
        i = j - 1;
        while (i >= 0 && sorted[i] > key) {
            sorted[i + 1] = sorted[i];
            i--; 

        }
        sorted[i + 1] = key;        
 

}
    return sorted;
}
//merge sort
int* merge_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    Merge_sorting(sorted, 0, n - 1);
    return sorted;
}

//heap sort
int* heap_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    Build_Max_heap(sorted, n);
    int tmp;
    int heap_size = n;
    for (int j = n - 1; j > 0; j--) {
        tmp = sorted[0];
        sorted[0] = sorted[j];
        sorted[j] = tmp;
        heap_size--;
        Max_heapify(sorted, 0, heap_size);

    }
    return sorted;
}
//quick sort(last element pivot)
int* quick_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    Quick_sorting(sorted, 0, n-1);
    return sorted;
}
//quick sort(randomized pivot)
int* randomized_quick_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    Randomized_Quick_sorting(sorted, 0, n - 1);
    return sorted;

}
//stooge sort
int* stooge_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    Stooge_sorting(sorted, 0,n-1);
    return sorted;


}
//radix sort
int* radix_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    int maxnum = 0;
    for (int i = 0; i < n; i++) {
        if (maxnum < arr[i]) {
            maxnum = arr[i];
        }
    }
    int maxnum_exp = 1;
    while ((maxnum / 10) > 0) {
        maxnum_exp++;
        maxnum = maxnum / 10;
    }

    for (int i = 1; i <= maxnum_exp; i++) {
        sorted = Counting_sort(sorted, n, i);
    }
    return sorted;
}


int main(void) {
    system_clock::time_point begin;
    double duration;
    bool is_sorted;
    int* arr;
    int n;

    // example of gen_data
    /*arr = gen_data(10);
    cout << "Example: ";
    print_arr(arr, 10);
    delete[] arr;*/

    n = 100000000;
    begin = system_clock::now();
    arr = gen_data(n,2);
    duration = duration_cast<milliseconds>(system_clock::now() - begin).count() / 1000.0;
    cout << "Time for gen data: " << duration << "s" << endl;

    begin = system_clock::now();
    int* sorted = merge_sort(arr, n);
    duration = duration_cast<milliseconds>(system_clock::now() - begin).count() / 1000.0;
    cout << "Time for sort: " << duration << "s" << endl;

    is_sorted = check_sorted(sorted, n);
    cout << "Sorted(1: true, 0:false): " << check_sorted(sorted, n) << endl;
    if (!is_sorted) {
        cout << "Try the implementation again" << endl;
    }
    delete[] sorted;

    delete[] arr;
    return 0;
}