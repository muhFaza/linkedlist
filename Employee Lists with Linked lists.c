//2502141990
//Muhammad Faza
//Compiler - Dev C++
//Data Structures

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inputdata();
int viewdata();
int delete();
int deleteall();
int out();

struct NodeEmployee{
    int id; //employee id
    char name[30];
    char pob[30]; //place of birth
    char dob[30]; //date of birth dd/mm/yyyy
    char job[50]; //occupation
    struct NodeEmployee* next;
};
struct NodeEmployee* Head = NULL;

struct NodeEmployee* CreateNewNode(int id, char name[], char pob[], char dob[], char job[]){
    struct NodeEmployee* NewNode = (struct NodeEmployee*) malloc(sizeof(struct NodeEmployee));
    NewNode->id = id;
    strcpy(NewNode->name, name);
    strcpy(NewNode->pob, pob);
    strcpy(NewNode->dob, dob);
    strcpy(NewNode->job, job);
    NewNode->next = NULL;

    struct NodeEmployee* current = Head;

    if (Head == NULL) {
        Head = NewNode;
        return;
    }

    //sort data if needed
    else if(current->id > NewNode->id){
        NewNode->next = current;
        Head = NewNode;
    }
    else{
        while (current->next != NULL) {
            current = current->next;

            if(current->id > NewNode->id){
                NewNode->next = current;
                struct NodeEmployee* current2 = Head;
                while(current2->next != current){
                    current2 = current2->next;
                }
                current2->next = NewNode;
                return;
            }

        }
        current->next = NewNode;
    }

};

int viewdata(){
    struct NodeEmployee* current = Head;
    int i=1;

    if(current == NULL){
        printf("Tidak ada data.");
        getchar();
        return;
    }

    printf("Data Karyawan\n");
    printf("=============\n\n");

    while(current != NULL){
        printf("%d.\n", i);
        printf("ID Karyawan: %d\n", current->id);
        printf("Nama Karyawan: %s\n", current->name);
        printf("Tempat Lahir: %s\n", current->pob);
        printf("Tanggal Lahir: %s\n", current->dob);
        printf("Jabatan: %s\n\n", current->job);

        current = current->next;
        i++;
    }
    printf("\nEND of DATA.\n\n");
    getchar();
}

void menu(){
    int id;
    char name[30];
    char pob[30];
    char dob[30];
    char job[50];
    char tempo[99]; //for validating if input below 30 char.

    int selectMenu;
    while(1){
        system("cls");
        printf("   PROGRAM DATA KARYAWAN\n");
        printf("============================\n\n");
        printf("1. Input Data Karyawan\n");
        printf("2. Daftar Karyawan\n");
        printf("3. Hapus Data Karyawan\n");
        printf("4. Hapus SEMUA Data Karyawan\n");
        printf("5. Keluar Program\n\n");

        printf("Masukkan Input: ");
        scanf("%d", &selectMenu); getchar();

        if(selectMenu == 1){
            //system("cls");
            inputdata(&id, name, pob, dob, job, tempo);
            CreateNewNode(id, name, pob, dob, job);

        }
        else if(selectMenu == 2){
            system("cls"); viewdata();
        }
        else if(selectMenu == 3){
            system("cls"); delete();
        }
        else if(selectMenu == 4){
//            system("cls");

            deleteall();
        }
        else if(selectMenu == 5){
            break;
        }
        else{
        printf("input tidak dikenal");
        getchar();
        system("cls");
        }
    }
}

int DupeID(int **pId){  //cek jika ada id yang sama
    struct NodeEmployee* current = Head;
    while(current != NULL){
        if(current->id   == **pId){
            return 1;
        }
        current = current->next;
    }

    return 0;
}

int inputdata(int *pId, char name[30], char pob[30], char dob[30], char job[50], char tempo[99]){
    int temp;
    struct NodeEmployee* current = Head;

    while(1){   //digunakan untuk konfirmasi jika data sudah benar.
        printf("\n\nInput Data Karyawan.\n");
        printf("====================\n\n");

        while(1){   //validasi id karyawan 5 digit
            current = Head;
            printf("ID Karyawan: ");
            scanf("%d", &temp); getchar();
            if(temp < 99999){
                *pId = temp;
                if (Head == NULL) {
                    break;
                }
                else{   //cek jika ada id yang sama
                    if(DupeID(&pId)){
                        printf("ID Karyawan Sudah Ada!\n\n");
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                printf("ID Karyawan Maksimum 5 Digit!\n\n");
            }
        }

        while(1){   //validasi nama <= 30
            printf("Nama Karyawan: ");
            scanf("%[^\n]", tempo); getchar();
            if (strlen(tempo) <= 30){
                strcpy(name, tempo);
                break;
            }
            else{
                printf("Maksimum 30 Karakter!\n\n");
            }
        }

        while(1){   //validasi tempat <= 30
            printf("Tempat Lahir: ");
            scanf("%[^\n]", tempo); getchar();
            if (strlen(tempo) <= 30){
                strcpy(pob, tempo);
                break;
            }
            else{
                printf("Maksimum 30 Karakter!\n\n");
            }
        }

        printf("Tanggal Lahir (dd/mm/yyyy): ");
        scanf("%[^\n]", dob); getchar();

        while(1){   //validasi jabatan <= 30
            printf("Jabatan: ");
            scanf("%[^\n]", tempo); getchar();
            if (strlen(tempo) <= 30){
                strcpy(job, tempo);
                break;
            }
            else{
                printf("Maksimum 30 Karakter!\n\n");
            }
        }
        printf("\n\nApakah data tersebut sudah benar?\n");
        printf("1. Sudah Benar\n");
        printf("2. Ulang Input Data\n\n");
        printf("Masukkan Input: ");
        scanf("%d", &temp); getchar();

        if(temp == 1){
            printf("\nData tersimpan!\n\n");
            break;
        }
    }
}

struct NodeEmployee *pCurrent;//var to save the address of current from FindID
int FindID(int *pDel){
    struct NodeEmployee* current = Head;
    while(current != NULL){
        if(current->id   == *pDel){
            pCurrent = current;
            printf("\n\nMenghapus data berikut.\n");
            printf("ID Karyawan: %d\n", current->id);
            printf("Nama Karyawan: %s\n", current->name);
            printf("Tempat Lahir: %s\n", current->pob);
            printf("Tanggal Lahir: %s\n", current->dob);
            printf("Jabatan: %s\n\n", current->job);
            return 0;
        }
        current = current->next;
    }
    return 1;
}

int delete(int **pDel){
    int del;
    struct NodeEmployee* current = Head;

    if(current == NULL){
        printf("Tidak ada data.");
        getchar();
        return;
    }

    printf("Hapus Data Karyawan\n");
    printf("===================\n\n");
    while(current != NULL){
        printf("ID: %d\n", current->id);
        current = current->next;
    }
    current = Head;
    printf("\nMasukkan Employee ID: ");
    scanf("%d", &del); getchar();

    if(FindID(&del)){
        printf("ID Tidak Ditemukan.");
        getchar();
        return;
    }
    else{
        //if its the only node
        if(pCurrent->next == NULL && pCurrent == Head){
            free(pCurrent);
            Head = NULL;
        }
        //if its the head node
        else if(Head == pCurrent){
            current = current->next;
            Head = current;
            free(pCurrent);
        }
        //if its the tail node
        else if(pCurrent->next == NULL){
            while(current->next != pCurrent){
                current = current->next;
            }
            current->next = NULL;
            free(pCurrent);
        }
        //if its the mid node
        else{
            while(current->next != pCurrent){
                current = current->next;
            }
//            struct NodeEmployee* current2 = pCurrent;
//            current2 = current2->next;
//            current->next = current2;
            current->next = pCurrent->next;
            free(pCurrent);
        }
    }
    printf("Data terhapus!");
    getchar();
}

int deleteall(){
    if(Head == NULL){
        system("cls");
        printf("Tidak ada data.");
        getchar();
        return;
    }

    printf("\n\nYakin menghapus SEMUA data karyawan?\n");
    printf("Input '1' jika setuju.\n\n");
    printf("Masukkan Input: ");
    int temp;
    scanf("%d", &temp); getchar();
    if(temp =! 1){
        return;
    }

    struct NodeEmployee* current = Head;
    pCurrent = Head;

    while(pCurrent != NULL){
        pCurrent = pCurrent->next;
        free(current);
        current = pCurrent;
    }
    Head = NULL;
    printf("Data terhapus!");
    getchar();
}


int main(){
    menu();

    return 0;
}
