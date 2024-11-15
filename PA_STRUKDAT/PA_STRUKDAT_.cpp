#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <limits>
using namespace std;

int pilihan;

struct user {
    int id;
    string username, password;
};

struct order {
    int order_id;
    int album_id;
    int user_id;
    string status; // "Pending", "Cancel", "Done"
};

struct album {
    int id, jumlah_stok, harga;
    string nama, nama_artist;
};

struct Node {
    album data;
    Node* next;
    Node* prev;  // Tambahkan pointer ke node sebelumnya
};

map<string, string> users; // Menyimpan username dan password user
vector<order> orders;      // Menyimpan data pemesanan

string admin_username = "admin";
string admin_password = "admin123";

Node* head = nullptr;
Node* tail = nullptr;  // Tambahkan pointer ke node terakhir

// Deklarasi fungsi login, menu admin, dan menu user
void login();
void admin_menu();
void user_menu(int userId);
// void // tampil();
void crud_menu(int loginStatus);  // Mengubah menu CRUD dengan loginStatus

void TAMPIL() {
    if (head == nullptr) {
        cout << "-------------------------------------------" << endl;
        cout << "|       DATA KOSONG, PILIH MENU 1!!       |" << endl;
        cout << "-------------------------------------------" << endl;
    } else {
        Node* current = head;
        cout << "-------------------------------------------" << endl;
        cout << "|            MENAMPILKAN DATA             |" << endl;
        cout << "-------------------------------------------" << endl;
        while (current != nullptr) {
            album a = current->data;
            cout << "DATA        : " << a.id << endl;
            cout << "NAMA ALBUM  : " << a.nama << endl;
            cout << "ARTIST      : " << a.nama_artist << endl;
            cout << "STOK ALBUM  : " << a.jumlah_stok << endl;
            cout << "HARGA ALBUM : " << a.harga << endl;
            cout << "-------------------------------------------" << endl;
            current = current->next;
        }
    }
    cout << "-------------------------------------------" << endl;
    cout << "|    TEKAN ENTER UNTUK KEMBALI KE MENU    |" << endl;
    cout << "-------------------------------------------" << endl;
    cin.ignore();
    cin.get();
}

void tampil() {
    int pilihan;
    do {
        cout << "-------------------------------------------" << endl;
        cout << "|          MENAMPILKAN DATA ALBUM         |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "|             1. FORWARD                  |" << endl;
        cout << "|             2. BACK TO MENU             |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Pilih [1-3] : ";
        cin >> pilihan;
        system("cls");
        if (cin.fail()) { // Jika input bukan angka
            cin.clear(); // Menghapus kesalahan pada cin
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Membersihkan buffer
            cout << "Input tidak valid. Masukkan angka 1-3." << endl;
            continue; // Kembali ke awal loop
        }

        switch (pilihan) {
            case 1:
                TAMPIL();
                break;
            case 2:
                crud_menu(-1); // Kembali ke menu utama
                break;
            default:
                cout << "------------------------------------------------" << endl;
                cout << "|   PILIHAN YANG ANDA MASUKKAN TIDAK TERSEDIA  |" << endl;
                cout << "|           SILAHKAN PILIH KEMBALI             |" << endl;
                cout << "------------------------------------------------" << endl;
                break;
        }
    } while (pilihan != 3); // Keluar dari loop saat pilihan adalah 3
}

void register_user() {
    string username, password;
    cout << "-------------------------------------------" << endl;
    cout << "|           REGISTRATION SYSTEM           |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // Check for empty username or password
    if (username.empty() || password.empty()) {
        cout << "Error: Username or password cannot be empty." << endl;
        return;
    }

    // Check if username already exists
    if (users.find(username) != users.end()) {
        cout << "Error: Username already taken. Please choose a different one." << endl;
        return;
    }

    // Register the user
    users[username] = password;
    cout << "Registration successful! You can now log in." << endl;
}


// Implementasi fungsi login

void login() {
    string username, password;
    int login_attempts = 0; // Counter for login attempts
    while (login_attempts < 3) {
        cout << "-------------------------------------------" << endl;
        cout << "|               LOGIN SYSTEM              |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if (username == admin_username && password == admin_password) {
            cout << "Login sebagai admin berhasil." << endl;
            admin_menu();
        } else if (users.find(username) != users.end() && users[username] == password) {
            cout << "Login sebagai user berhasil." << endl;
            int userId = 0;
            for (auto &user : users) {
                if (user.first == username) {
                    userId++;
                    break;
                }
            }
            user_menu(userId);
        } else {
            login_attempts++;
            if (users.find(username) == users.end()) {
                cout << "Error: Username does not exist." << endl;
            } else if (users[username] != password) {
                cout << "Error: Incorrect password." << endl;
            } else {
                cout << "Username atau password salah." << endl;
            }
        }

        if (login_attempts >= 3) {
            cout << "Login gagal 3 kali. Program akan keluar." << endl;
            exit(0); // Exiting program on 3 failed attempts
        }
    }
}

// Menu login untuk program
void login_menu() {
    int pilihan;
    do {
        cout << "-------------------------------------------" << endl;
        cout << "|                 MENU UTAMA              |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "| 1. Login                                |" << endl;
        cout << "| 2. Registrasi User                      |" << endl;
        cout << "| 3. Keluar                               |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Pilih [1-3]: ";
        cin >> pilihan;
        if (pilihan == 1) {
            login();
        } else if (pilihan == 2) {
             register_user();
        }
    } while (pilihan != 3);
    cout << "Terima kasih telah menggunakan program." << endl;
}

// Fungsi untuk admin
void admin_menu() {
    int pilihan;
    do {
        cout << "-------------------------------------------" << endl;
        cout << "|               ADMIN MENU                |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "| 1. Lihat Semua Pesanan                  |" << endl;
        cout << "| 2. Ubah Status Pesanan                  |" << endl;
        cout << "| 3. CRUD Data Album                      |" << endl;
        cout << "| 4. Logout                               |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Pilih [1-4]: ";
        cin >> pilihan;

        if (pilihan == 1) {
            // Tampilkan semua pesanan
            for (const auto &order : orders) {
                cout << "Order ID: " << order.order_id << endl;
                cout << "Album ID: " << order.album_id << endl;
                cout << "User ID: " << order.user_id << endl;
                cout << "Status: " << order.status << endl;
                cout << "-------------------------------------------" << endl;
            }
        } else if (pilihan == 2) {
            int order_id;
            string new_status;
            cout << "Masukkan ID Pesanan: ";
            cin >> order_id;
            cout << "Status Baru (Pending, Cancel, Done): ";
            cin >> new_status;
            bool found = false;
            for (auto &order : orders) {
                if (order.order_id == order_id) {
                    order.status = new_status;
                    cout << "Status pesanan berhasil diubah." << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Pesanan dengan ID tersebut tidak ditemukan." << endl;
            }
        } else if (pilihan == 3) {
            // Panggil menu CRUD khusus untuk admin
            crud_menu(-1); // Pastikan -1 adalah loginStatus untuk admin
        } else if (pilihan == 4) {
            cout << "Logout berhasil. Kembali ke menu login." << endl;
            login_menu(); // Arahkan ke login_menu
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 4);
}

// Fungsi untuk user
void user_menu(int userId) {
    int pilihan;
    do {
        cout << "-------------------------------------------" << endl;
        cout << "|               USER MENU                 |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "| 1. Lihat Album                          |" << endl;
        cout << "| 2. Pesan Album                          |" << endl;
        cout << "| 3. Riwayat Pembelian                    |" << endl;
        cout << "| 4. Logout                               |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Pilih [1-4]: ";
        cin >> pilihan;
        if (pilihan == 1) {
            TAMPIL();
        } else if (pilihan == 2) {
            int album_id;
            cout << "Masukkan ID Album yang ingin dibeli: ";
            cin >> album_id;
            order new_order = {static_cast<int>(orders.size() + 1), album_id, userId, "Pending"};
            orders.push_back(new_order);
            cout << "Pesanan berhasil dibuat dengan status 'Pending'." << endl;
        } else if (pilihan == 3) {
            cout << "-------------------------------------------" << endl;
            cout << "|          RIWAYAT PEMBELIAN             |" << endl;
            cout << "-------------------------------------------" << endl;
            for (const auto &order : orders) {
                if (order.user_id == userId) {
                    cout << "Order ID: " << order.order_id << endl;
                    cout << "Album ID: " << order.album_id << endl;
                    cout << "Status: " << order.status << endl;
                    cout << "-------------------------------------------" << endl;
                }
            }
        }
    } while (pilihan != 4);
}




void SORTING();
void SEARCHING();


void TAMBAH() {
    system("cls");
    string ulang;
    while (ulang != "n") {
        Node* new_node = new Node;
        new_node->next = nullptr;
        new_node->prev = nullptr;

        cout << "-------------------------------------------" << endl;
        cout << "|            MENAMBAHKAN DATA             |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Nama Album        : ";
        fflush(stdin);
        getline(cin, new_node->data.nama);
        cout << "Nama Artist       : ";
        fflush(stdin);
        getline(cin, new_node->data.nama_artist);
        cout << "Jumlah Stok Album : ";
        cin >> new_node->data.jumlah_stok;
        cout << "Harga Album       : ";
        cin >> new_node->data.harga;
        cout << "-------------------------------------------" << endl;

        // Menentukan ID baru
        int new_id = 1;  // ID awal
        if (tail != nullptr) {
            new_id = tail->data.id + 1;  // ID baru adalah ID terakhir + 1
        }
        new_node->data.id = new_id;

        // Tambahkan di akhir daftar
        if (tail == nullptr) {
            // Jika daftar kosong
            head = new_node;
            tail = new_node;
        } else {
            // Jika daftar tidak kosong
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }

        cout << endl;
        cout << "-------------------------------------------" << endl;
        cout << "|      SUKSES MENAMBAHKAN DATA ALBUM      |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Ingin menambah data lagi? [y/n] : ";
        cin >> ulang;
        cout << "-------------------------------------------" << endl;
        system("cls");
    }
    cout << "-------------------------------------------" << endl;
    cout << "|    TEKAN ENTER UNTUK KEMBALI KE MENU    |" << endl;
    cout << "-------------------------------------------" << endl;
    cin.ignore();
    cin.get();
}




void UBAH() {
    if (head == nullptr) {
        cout << "-------------------------------------------" << endl;
        cout << "|       DATA KOSONG, PILIH MENU 1!!       |" << endl;
        cout << "-------------------------------------------" << endl;
    } else {
        int idToUbah;
        cout << "-------------------------------------------" << endl;
        cout << "|              MENGUBAH DATA              |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Masukkan ID Album yang Ingin Diubah : ";
        cin >> idToUbah;
        cout << "-------------------------------------------" << endl;

        Node* current = head;
        bool found = false;

        while (current != nullptr) {
            album a = current->data;
            if (a.id == idToUbah) {
                cout << "Ubah Data Album Nomor " << a.id << endl;
                cout << "-------------------------------------------" << endl;
                cout << "Nama Album Terbaru        : ";
                cin.ignore();
                getline(cin, a.nama);
                cout << "Nama Artist Terbaru       : ";
                getline(cin, a.nama_artist);
                cout << "Jumlah Stok Album Terbaru : ";
                cin >> a.jumlah_stok;
                cout << "Harga Album Terbaru       : ";
                cin >> a.harga;
                cout << "-------------------------------------------" << endl;
                current->data = a;
                found = true;
                break;
            }
            current = current->next;
        }

        if (found) {
            cout << "-------------------------------------------" << endl;
            cout << "|       SUKSES MENGUBAH DATA ALBUM        |" << endl;
            cout << "-------------------------------------------" << endl;
        } else {
            cout << "-------------------------------------------" << endl;
            cout << "| Album dengan ID " << idToUbah << " tidak ditemukan |" << endl;
            cout << "-------------------------------------------" << endl;
        }
    }
    cout << "-------------------------------------------" << endl;
    cout << "|    TEKAN ENTER UNTUK KEMBALI KE MENU    |" << endl;
    cout << "-------------------------------------------" << endl;
    cin.ignore();
    cin.get();
}

void HAPUS() {
    if (head == nullptr) {
        cout << "-------------------------------------------" << endl;
        cout << "|       DATA KOSONG, PILIH MENU 1!!       |" << endl;
        cout << "-------------------------------------------" << endl;
    } else {
        int id;
        cout << "-------------------------------------------" << endl;
        cout << "|             MENGHAPUS DATA              |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Hapus Data Album Nomor : ";
        cin >> id;
        cout << "-------------------------------------------" << endl;

        Node* current = head;

        while (current != nullptr) {
            album a = current->data;
            if (a.id == id) {
                if (current->prev == nullptr) {
                    // Hapus node pertama
                    head = current->next;
                    if (current->next != nullptr) {
                        current->next->prev = nullptr;
                    }
                } else {
                    // Hapus node selain node pertama
                    current->prev->next = current->next;
                    if (current->next != nullptr) {
                        current->next->prev = current->prev;
                    }
                }
                delete current;
                cout << "-------------------------------------------" << endl;
                cout << "|      SUKSES MENGHAPUS DATA ALBUM        |" << endl;
                cout << "-------------------------------------------" << endl;
                cin.ignore();
                cin.get();
                return;
            }
            current = current->next;
        }

        cout << "-------------------------------------------" << endl;
        cout << "|           DATA TIDAK DITEMUKAN          |" << endl;
        cout << "-------------------------------------------" << endl;
    }

    cout << "-------------------------------------------" << endl;
    cout << "|    TEKAN ENTER UNTUK KEMBALI KE MENU    |" << endl;
    cout << "-------------------------------------------" << endl;
    cin.ignore();
    cin.get();
}

void ShellSort(album* arr, int n, bool ascending) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            album temp = arr[i];
            int j;

            if (ascending) {
                for (j = i; j >= gap && arr[j - gap].nama > temp.nama; j -= gap) {
                    arr[j] = arr[j - gap];
                }
            } else { // descending
                for (j = i; j >= gap && arr[j - gap].nama < temp.nama; j -= gap) {
                    arr[j] = arr[j - gap];
                }
            }

            arr[j] = temp;
        }
    }
}

void AscShell() {
    if (head == nullptr) {
        cout << "-------------------------------------------" << endl;
        cout << "   Data kosong, isi data terlebih dahulu.  " << endl;
        cout << "-------------------------------------------" << endl;
        return;
    }

    int n = 0;
    Node* current = head;
    while (current != nullptr) {
        n++;
        current = current->next;
    }

    album* arr = new album[n];
    current = head;
    int i = 0;

    while (current != nullptr) {
        arr[i] = current->data;
        current = current->next;
        i++;
    }

    ShellSort(arr, n, true);

    current = head;
    i = 0;

    while (current != nullptr) {
        current->data = arr[i];
        current = current->next;
        i++;
    }

    delete[] arr;
    TAMPIL();
    system("cls");
}

void DescShell() {
    if (head == nullptr) {
        cout << "-------------------------------------------" << endl;
        cout << "   Data kosong, isi data terlebih dahulu.  " << endl;
        cout << "-------------------------------------------" << endl;
        return;
    }

    int n = 0;
    Node* current = head;
    while (current != nullptr) {
        n++;
        current = current->next;
    }

    album* arr = new album[n];
    current = head;
    int i = 0;

    while (current != nullptr) {
        arr[i] = current->data;
        current = current->next;
        i++;
    }

    ShellSort(arr, n, false);

    current = head;
    i = 0;

    while (current != nullptr) {
        current->data = arr[i];
        current = current->next;
        i++;
    }

    delete[] arr;
    TAMPIL();
    system("cls");
}

int partition(album* arr, int low, int high, bool ascending) {
    int pivot = arr[high].jumlah_stok;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if ((ascending && arr[j].jumlah_stok < pivot) || (!ascending && arr[j].jumlah_stok > pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(album* arr, int low, int high, bool ascending) {
    if (low < high) {
        int pi = partition(arr, low, high, ascending);

        quickSort(arr, low, pi - 1, ascending);
        quickSort(arr, pi + 1, high, ascending);
    }
}

void AscQuick() {
    if (head == nullptr) {
        cout << "-------------------------------------------" << endl;
        cout << "   Data kosong, isi data terlebih dahulu.  " << endl;
        cout << "-------------------------------------------" << endl;
        return;
    }

    int n = 0;
    Node* current = head;
    while (current != nullptr) {
        n++;
        current = current->next;
    }

    album* arr = new album[n];
    current = head;
    int i = 0;

    while (current != nullptr) {
        arr[i] = current->data;
        current = current->next;
        i++;
    }

    quickSort(arr, 0, n - 1, true);

    current = head;
    i = 0;

    while (current != nullptr) {
        current->data = arr[i];
        current = current->next;
        i++;
    }

    delete[] arr;
    TAMPIL();
    system("cls");
}

void DescQuick() {
    if (head == nullptr) {
        cout << "-------------------------------------------" << endl;
        cout << "   Data kosong, isi data terlebih dahulu.  " << endl;
        cout << "-------------------------------------------" << endl;
        return;
    }

    int n = 0;
    Node* current = head;
    while (current != nullptr) {
        n++;
        current = current->next;
    }

    album* arr = new album[n];
    current = head;
    int i = 0;

    while (current != nullptr) {
        arr[i] = current->data;
        current = current->next;
        i++;
    }

    quickSort(arr, 0, n - 1, false);

    current = head;
    i = 0;

    while (current != nullptr) {
        current->data = arr[i];
        current = current->next;
        i++;
    }

    delete[] arr;
    TAMPIL();
    system("cls");
}

void merge(album* arr, int left, int mid, int right, bool ascending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    album* leftArr = new album[n1];
    album* rightArr = new album[n2];

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (ascending) {
            if (leftArr[i].harga <= rightArr[j].harga) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
        } else {
            if (leftArr[i].harga >= rightArr[j].harga) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(album* arr, int left, int right, bool ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, ascending);
        mergeSort(arr, mid + 1, right, ascending);

        merge(arr, left, mid, right, ascending);
    }
}

void AscMerge() {
    if (head == nullptr) {
        cout << "-------------------------------------------" << endl;
        cout << "   Data kosong, isi data terlebih dahulu.  " << endl;
        cout << "-------------------------------------------" << endl;
        return;
    }

    int n = 0;
    Node* current = head;
    while (current != nullptr) {
        n++;
        current = current->next;
    }

    album* arr = new album[n];
    current = head;
    int i = 0;

    while (current != nullptr) {
        arr[i] = current->data;
        current = current->next;
        i++;
    }

    mergeSort(arr, 0, n - 1, true);

    current = head;
    i = 0;

    while (current != nullptr) {
        current->data = arr[i];
        current = current->next;
        i++;
    }

    delete[] arr;
    TAMPIL();
    system("cls");
}

void DescMerge() {
    if (head == nullptr) {
        cout << "-------------------------------------------" << endl;
        cout << "   Data kosong, isi data terlebih dahulu.  " << endl;
        cout << "-------------------------------------------" << endl;
        return;
    }

    int n = 0;
    Node* current = head;
    while (current != nullptr) {
        n++;
        current = current->next;
    }

    album* arr = new album[n];
    current = head;
    int i = 0;

    while (current != nullptr) {
        arr[i] = current->data;
        current = current->next;
        i++;
    }

    mergeSort(arr, 0, n - 1, false);

    current = head;
    i = 0;

    while (current != nullptr) {
        current->data = arr[i];
        current = current->next;
        i++;
    }

    delete[] arr;
    TAMPIL();
    system("cls");
}

void SHELLMENU() {
    cout << "-------------------------------------------" << endl;
    cout << "|             SORTING NAMA ALBUM          |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "|               1. ASCENDING              |" << endl;
    cout << "|               2. DESCENDING             |" << endl;
    cout << "|               3. SORTING MENU           |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Pilih [1-3] : ";
    cin >> pilihan;
    system("cls");
    do {
        if (pilihan == 1) {
            AscShell();
            SHELLMENU();
        }
        if (pilihan == 2) {
            DescShell();
            SHELLMENU();
        }
        if (pilihan == 3) {
            SORTING();
        }
    } while (pilihan <= 3);
    if (pilihan > 3) {
        cout << "------------------------------------------------" << endl;
        cout << "|   PILIHAN YANG ANDA MASUKKAN TIDAK TERSEDIA  |" << endl;
        cout << "|           SILAHKAN PILIH KEMBALI             |" << endl;
        cout << "------------------------------------------------" << endl;
        SHELLMENU();
    }
}

void QUICKMENU() {
    cout << "-------------------------------------------" << endl;
    cout << "|            SORTING JUMLAH ALBUM         |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "|               1. ASCENDING              |" << endl;
    cout << "|               2. DESCENDING             |" << endl;
    cout << "|               3. SORTING MENU           |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Pilih [1-3] : ";
    cin >> pilihan;
    system("cls");
    do {
        if (pilihan == 1) {
            AscQuick();
            QUICKMENU();
        }
        if (pilihan == 2) {
            DescQuick();
            QUICKMENU();
        }
        if (pilihan == 3) {
            SORTING();
        }
    } while (pilihan <= 3);
    if (pilihan > 3) {
        cout << "------------------------------------------------" << endl;
        cout << "|   PILIHAN YANG ANDA MASUKKAN TIDAK TERSEDIA  |" << endl;
        cout << "|           SILAHKAN PILIH KEMBALI             |" << endl;
        cout << "------------------------------------------------" << endl;
        QUICKMENU();
    }
}

void MERGEMENU() {
    cout << "-------------------------------------------" << endl;
    cout << "|            SORTING HARGA ALBUM          |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "|               1. ASCENDING              |" << endl;
    cout << "|               2. DESCENDING             |" << endl;
    cout << "|               3. SORTING MENU           |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Pilih [1-3] : ";
    cin >> pilihan;
    system("cls");
    do {
        if (pilihan == 1) {
            AscMerge();
            MERGEMENU();
        }
        if (pilihan == 2) {
            DescMerge();
            MERGEMENU();
        }
        if (pilihan == 3) {
            SORTING();
        }
    } while (pilihan <= 3);
    if (pilihan > 3) {
        cout << "------------------------------------------------" << endl;
        cout << "|   PILIHAN YANG ANDA MASUKKAN TIDAK TERSEDIA  |" << endl;
        cout << "|           SILAHKAN PILIH KEMBALI             |" << endl;
        cout << "------------------------------------------------" << endl;
        MERGEMENU();
    }
}

void SORTING() {
    system("cls");
    cout << "-------------------------------------------" << endl;
    cout << "|          S O R T I N G M E N U          |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "|        1. SHELL SORT (NAMA ALBUM)       |" << endl;
    cout << "|        2. QUICK SORT (JUMLAH)           |" << endl;
    cout << "|        3. MERGE SORT (HARGA)            |" << endl;
    cout << "|        4. BACK TO MENU                  |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Pilih [1-4] : ";
    cin >> pilihan;
    system("cls");
    do {
        if (pilihan == 1) {
            SHELLMENU();
            system("cls");
            SORTING();
        }
        if (pilihan == 2) {
            QUICKMENU();
            system("cls");
            SORTING();
        }
        if (pilihan == 3) {
            MERGEMENU();
            system("cls");
            SORTING();
        }
        if (pilihan == 4) {
            system("cls");
            crud_menu(-1);
        }
    } while (pilihan <= 4);
    if (pilihan > 4) {
        cout << "------------------------------------------------" << endl;
        cout << "|   PILIHAN YANG ANDA MASUKKAN TIDAK TERSEDIA  |" << endl;
        cout << "|           SILAHKAN PILIH KEMBALI             |" << endl;
        cout << "------------------------------------------------" << endl; 
        SORTING();
    }
}

Node* FibonacciSearchAll1(int id) {
    int length = 0;
    Node* current = head;
    Node* result_head = nullptr;  // Head dari linked list hasil pencarian
    Node* result_tail = nullptr;  // Elemen terakhir dalam linked list hasil pencarian

    while (current != nullptr) {
        if (current->data.id == id) 
        {
            Node* new_node = new Node;
            new_node->data = current->data;
            new_node->next = nullptr;

            if (result_head == nullptr) {
                result_head = new_node;
                result_tail = new_node;
            } else {
                result_tail->next = new_node;
                result_tail = new_node;
            }
        }

        length++;
        current = current->next;
    }

    return result_head;  // Kembalikan head dari linked list hasil
}

void FIBONACCI1() {
    int targetid;
    if (head == nullptr) {
        cout << "-------------------------------------------" << endl;
        cout << "|  Data kosong, isi data terlebih dahulu. |" << endl;
        cout << "-------------------------------------------" << endl;
        return;
    }

    cout << "-------------------------------------------" << endl;
    cout << "Masukkan ID yang ingin Anda cari: ";
    cin >> targetid;

    Node* current = head;
    bool found = false;

    while (current != nullptr) {
        if (current->data.id == targetid) {
            found = true;
            cout << "-------------------------------------------" << endl;
            cout << "Data dengan ID " << targetid << " ditemukan" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "Nama Album        : " << current->data.nama << endl;
            cout << "Nama Artist       : " << current->data.nama_artist << endl;
            cout << "Jumlah Stok Album : " << current->data.jumlah_stok << endl;
            cout << "Harga Album       : " << current->data.harga << endl;
            cout << "-------------------------------------------" << endl;
            break;
        }
        current = current->next;
    }

    if (!found) {
        cout << "-------------------------------------------" << endl;
        cout << "Data dengan ID " << targetid << " tidak ditemukan." << endl;
        cout << "-------------------------------------------" << endl;
    }

    cout << "-------------------------------------------" << endl;
    cout << "|    TEKAN ENTER UNTUK KEMBALI KE MENU    |" << endl;
    cout << "-------------------------------------------" << endl;
    cin.ignore();
    cin.get();
    system("cls");
}

Node* FibonacciSearchAll2(const string& nama_artist) {
    int length = 0;
    Node* current = head;
    Node* result_head = nullptr;  // Head dari linked list hasil pencarian
    Node* result_tail = nullptr;  // Elemen terakhir dalam linked list hasil pencarian

    while (current != nullptr) {
        if (current->data.nama_artist == nama_artist) {
            Node* new_node = new Node;
            new_node->data = current->data;
            new_node->next = nullptr;

            if (result_head == nullptr) {
                result_head = new_node;
                result_tail = new_node;
            } else {
                result_tail->next = new_node;
                result_tail = new_node;
            }
        }

        length++;
        current = current->next;
    }

    return result_head;  // Kembalikan head dari linked list hasil
}

void FIBONACCI2() {
    string targetNamaArtist;
    if (head == nullptr) {
        cout << "-------------------------------------------" << endl;
        cout << "|  Data kosong, isi data terlebih dahulu. |" << endl;
        cout << "-------------------------------------------" << endl;
        return;
    }

    cout << "-------------------------------------------" << endl;
    cout << "Masukkan Nama Artist" <<endl;
    cout << "yang ingin Anda cari : ";
    cin.ignore();
    getline(cin, targetNamaArtist);

    Node* current = head;
    bool found = false;

    while (current != nullptr) {
        if (current->data.nama_artist == targetNamaArtist) {
            if (!found) {
                cout << "-------------------------------------------" << endl;
                cout << "Nama Artist " << targetNamaArtist << " ditemukan" << endl;
                cout << "-------------------------------------------" << endl;
                found = true;
            }

            cout << "Nama Album        : " << current->data.nama << endl;
            cout << "Nama Artist       : " << current->data.nama_artist << endl;
            cout << "Jumlah Stok Album : " << current->data.jumlah_stok << endl;
            cout << "Harga Album       : " << current->data.harga << endl;
            cout << "-------------------------------------------" << endl;
        }
        current = current->next;
    }

    if (!found) {
        cout << "-------------------------------------------" << endl;
        cout << "Nama Artist " << targetNamaArtist << " tidak ditemukan." << endl;
        cout << "-------------------------------------------" << endl;
    }

    cout << "-------------------------------------------" << endl;
    cout << "|    TEKAN ENTER UNTUK KEMBALI KE MENU    |" << endl;
    cout << "-------------------------------------------" << endl;
    cin.ignore();
    cin.get();
    system("cls");
}

void SEARCHING() {
    cout << "-------------------------------------------" << endl;
    cout << "|        S E A R C H I N G M E N U        |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "|             1. ID ALBUM                 |" << endl;
    cout << "|             2. NAMA ARTIST              |" << endl;
    cout << "|             3. BACK TO MENU             |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Pilih [1-3] : ";
    cin >> pilihan;
    system("cls");
    do {
        if (pilihan == 1) {
            FIBONACCI1();
            SEARCHING();
        }
        if (pilihan == 2) {
            FIBONACCI2();
            SEARCHING();
        }
        if (pilihan == 3) {
            system("cls");
            crud_menu(-1);
        }
    } while (pilihan <= 4);
    if (pilihan > 4) {
        cout << "------------------------------------------------" << endl;
        cout << "|   PILIHAN YANG ANDA MASUKKAN TIDAK TERSEDIA  |" << endl;
        cout << "|           SILAHKAN PILIH KEMBALI             |" << endl;
        cout << "------------------------------------------------" << endl; 
        SEARCHING();
    }
}

// Menu CRUD utama untuk admin
void crud_menu(int loginStatus) {
    if (loginStatus == -1) {
        // CRUD hanya untuk admin (loginStatus = -1)
    cout << "-------------------------------------------" << endl;
    cout << "|             CRUD MENU ADMIN             |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "|         1. MENAMBAH DATA ALBUM          |" << endl;
    cout << "|         2. MENAMPILKAN DATA ALBUM       |" << endl;
    cout << "|         3. MENGUBAH DATA ALBUM          |" << endl;
    cout << "|         4. MENGHAPUS DATA ALBUM         |" << endl;
    cout << "|         5. SORTING                      |" << endl;
    cout << "|         6. SEARCHING                    |" << endl;
    cout << "|         7. E X I T                      |" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Pilih [1-7] : ";
    cin >> pilihan;
    system("cls");
    do {
        if (pilihan == 1) {
            TAMBAH();
            system("cls");
            crud_menu(-1);
        } else if (pilihan == 2) {
            tampil();
            system("cls");
            crud_menu(-1);
        } else if (pilihan == 3) {
            UBAH();
            system("cls");
            crud_menu(-1);
        } else if (pilihan == 4) {
            HAPUS();
            system("cls");
            crud_menu(-1);
        } else if (pilihan == 5) {
            SORTING();
            system("cls");
            crud_menu(-1);
        } else if (pilihan == 6) {
            SEARCHING();
            system("cls");
            crud_menu(-1);
        } else if (pilihan == 7) {
            system("cls");
            cout << "----------------------------------------" << endl;
            cout << "|    ANDA TELAH KELUAR DARI PROGRAM    |" << endl;
            cout << "|             TERIMA KASIH             |" << endl;
            cout << "----------------------------------------" << endl;
            login_menu(); 
            break;
            }

    } while (pilihan <= 7);
    if (pilihan > 7) {
        cout << "------------------------------------------------" << endl;
        cout << "|   PILIHAN YANG ANDA MASUKKAN TIDAK TERSEDIA  |" << endl;
        cout << "|           SILAHKAN PILIH KEMBALI             |" << endl;
        cout << "------------------------------------------------" << endl;
        crud_menu(-1);
        }
    } else {
        cout << "Hanya admin yang memiliki akses ke menu CRUD!" << endl;
    }
}
int main() {
    login_menu();
    return 0;
}



