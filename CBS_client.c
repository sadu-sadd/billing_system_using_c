#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_bill();   //function declarations 
void input();
void writefile();
void search();
void output();

struct account   //Customer account structure
{
    int number;
    char name[100];
    int acct_no;
    float mobile_no;
    char Taluk[100];
    char District[100];
} customer;

int tl, sl, ts;

// main function
int main()
{
    int i;
    int n;
    char ch;
    char x;
    system("clear");
    // Main menu
    printf("\t\t    CUSTOMER BILLING SYSTEM   \n\n");
    printf("==============================================================\n");
    printf("\t\t1: -->   Print Customer Bill\n");
    printf("\t\t2: -->   Add customer account\n");
    printf("\t\t3: -->   Search customer account\n");
    printf("\t\t4: -->   Exit\n");
    printf("\n==============================================================\n");

    do
    {
        printf("\nSelect the Option from menu : ");
        ch = getchar();
    } while (ch <= '0' || ch > '4');

    switch (ch)
    {
    case '1':
        system("clear");            //Print bill
        print_bill();
        scanf("%s",x);
        main();

    case '2':
        system("clear");            // Add customer account
        printf("\nHow many customer accounts ? : ");
        scanf("%d", &n);
        for (i = 0; i < n; i++)
        {
            input();
            writefile();
        }
        main();

    case '3':
        printf("Choose the method to search.\n");       //Search customer account by number or name
        printf("\n1. Search by customer number\n");
        printf("2. Search by customer name\n");
        search();
        ch = getchar();
        main();

    case '4':
        printf("\n");           //Exit from Billing system
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~ THANK YOU ~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\n");
        exit(1);
    }

    return 0;
}

//********************************************************************************************************

void print_bill()
{
    float bill, rate[10], GST;
    int i, n, bid, qty[10];
    char date[15], item[100][30], cname[50], phone[10],x;
    //system("clear");
    printf("\t\t\tCUSTOMER BILL");
    printf("\n_________________________________________________________________");
    printf("\n\nEnter the Bill id                     : ");
    scanf("%d", &bid);
    fflush(stdin);
    printf("\nEnter the name of Customer            : ");
    scanf("%s", cname);
    printf("\nEnter the Phone number of customer    : ");
    scanf("%s", phone);
    printf("\n\nHow many purchase items : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the %d item name : ", i + 1);
        fflush(stdin);
        scanf("%s", item[i]);
        printf("\nEnter the Quantity and Rate of %s item : ", item[i]);
        scanf("%d %f", &qty[i], &rate[i]);
        bill = bill + (rate[i] * qty[i]) + (5 / 100) * (rate[i] * qty[i]);
    }
    printf("\n\n************************ Billing Summary *************************");
    printf("\n\nBill id is= %d", bid);
    printf("\n\nDate= %s", date);
    printf("\n\nCustomer name= %s", cname);
    printf("\n\nPhone number=%s", phone);
    printf("\n\n\n-----------------------------------------------------------------------------");
    printf("\nItem name\t\tRate\t\tQty\t\tGST\t\tAmount\t\t\t\t\t\tDate : %s", date);
    printf("\n-----------------------------------------------------------------------------");
    for (i = 0; i < n; i++)
    {
        printf("\n\n%s\t\t\t%.2f\t\t%d\t\t%.2f\t\t%.2f", item[i], rate[i], qty[i], (5 * rate[i] /100), rate[i] * qty[i]);
    }
    printf("\n----------------------------------------------------------------------------");
    printf("\n\nTOTAL  = \t\t\t\t\t\t%.2f", bill);
    printf("\n\n-------------------------------------------------------------------");
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Visit Again ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    r.eturn;
}

void input()
{
    FILE *fp = fopen("account.dat", "ab");
    fseek(fp, 0, SEEK_END);
    tl = ftell(fp);
    sl = sizeof(customer);
    ts = tl / sl;
    fseek(fp, (ts - 1) * sl, SEEK_SET);
    fread(&customer, sizeof(customer), 1, fp);
    printf("\nCustomer no : %d\n", ++customer.number);
    fclose(fp);
    printf("      Account number  : ");
    scanf("%d", &customer.acct_no);
    printf("      Name            : ");
    scanf("%s", customer.name);
    printf("      Mobile no       : ");
    scanf("%f", &customer.mobile_no);
    printf("      Taluk           : ");
    scanf("%s", customer.Taluk);
    printf("      District        : ");
    scanf("%s", customer.District);
    return;
}

void writefile()
{
    FILE *fp;
    fp = fopen("account.dat", "ab");
    fwrite(&customer, sizeof(customer), 1, fp);
    fclose(fp);
    return;
}

void search()
{
    char choice;
    int chh;
    char nam[100];
    int n, i, m = 1;
    FILE *fp;
    fp = fopen("account.dat", "rb");
    do
    {
        printf("\nEnter your choice:");
        choice = getchar();

    } while (choice != '1' && choice != '2');
    switch (choice)
    {
    case '1':
        fseek(fp, 0, SEEK_END);
        tl = ftell(fp);
        sl = sizeof(customer);
        ts = tl / sl;
        do
        {
            printf("\nchoose customer number:");
            scanf("%d", &n);
            if (n <= 0 || n > ts)
                printf("\nenter correct\n");
            else
            {
                fseek(fp, (n - 1) * sl, SEEK_SET);
                fread(&customer, sl, 1, fp);
                output();
            }
            printf("\n\nagain?(y/n)");
            scanf("%d", &chh);
        } while (chh == 1);
        fclose(fp);
        break;
    case '2':
        fseek(fp, 0, SEEK_END);
        tl = ftell(fp);
        sl = sizeof(customer);
        ts = tl / sl;
        fseek(fp, (ts - 1) * sl, SEEK_SET);
        fread(&customer, sizeof(customer), 1, fp);
        n = customer.number;

        do
        {
            printf("\nenter the name:");
            scanf("%s", nam);
            fseek(fp, 0, SEEK_SET);
            for (i = 1; i <= n; i++)
            {
                fread(&customer, sizeof(customer), 1, fp);
                if (strcmp(customer.name, nam) == 0)
                {
                    output();
                    m = 0;
                    break;
                }
            }
            if (m != 0)
                printf("\n\ndoesn't exist\n");
            printf("\nanother?(y/n)");
            scanf("%d", &chh);
        } while (chh == 1);
        fclose(fp);
    }
    return;
}

void output()
{
    printf("\n\n    Customer no    :%d\n", customer.number);
    printf("    Name 	   :%s\n", customer.name);
    printf("    Mobile no      :%.f\n", customer.mobile_no);
    printf("    Account number :%d\n", customer.acct_no);
    return;
}
