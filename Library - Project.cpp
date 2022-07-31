/*1.	In a library, for each book book-id, serial number (denotes copy number of a book), title, 
author, publisher and price are stored. Book-id and serial number together will be unique identifier
 for a book. Members are either student or faculty. Each member has unique member-id. Name, e-mail, 
 address are also to be stored. For any transaction (book issue or return), members are supposed to 
 place transactions slip. User will submit member-id, book-id, and serial number (only for book return).
While processing a transaction, check the validity of the member. While issuing, availability of a copy
of the book is to be checked. While returning a book, it is to be checked whether this copy was issued
to the member or not. A student member can have 2 books issued at a point of time. For faculty members
it is 10. Transaction information is to be stored like date of transaction, member-id, book-id, serial
number, returned or not. An entry is made when book is issued and updated when the book is returned.
For storing the information consider files.
Design the classes and implement. 

BOOK->BOOKLIST
MEMBER->STUDENT->STUDENTMEMBERLIST
      ->FACULTY -> FACULTYMEMBERLIST
TRANSACTION ->TRANSCATIONLIST
LIBRARY      

*/

#include <iostream>
#include<fstream>
#include <string.h>
#include <time.h>
using namespace std;

#define ISSUE_LIMIT_STUDENT 2
#define ISSUE_LIMIT_FACULTY 10


// Book
class BOOK
{
private:
    string id;
    string serialNo;
    string title;
    string author;
    string publisher;
    int price;

public:
    BOOK() {}
    BOOK(string id, string serialNo, string title, string author, string publisher, float price);
    void display();
    bool isSameBook(string id, string serialNo);

    friend ostream& operator<<(ostream& os, const BOOK& book);
    friend istream& operator>>(istream& is, BOOK& book);
};

ostream& operator<<(ostream& os, const BOOK& book)
{
    char tmp[100];
    strcpy(tmp, book.id.c_str());
    os.write(tmp, sizeof(tmp));
    strcpy(tmp, book.serialNo.c_str());
    os.write(tmp, sizeof(tmp));
    strcpy(tmp, book.title.c_str());
    os.write(tmp, sizeof(tmp));
    strcpy(tmp, book.author.c_str());
    os.write(tmp, sizeof(tmp));
    strcpy(tmp, book.publisher.c_str());
    os.write(tmp, sizeof(tmp));
    snprintf(tmp, sizeof(tmp), "%d" ,book.price);
    os.write(tmp, sizeof(tmp));
    return os;
}
istream& operator>>(istream& is, BOOK& book){
    char tmp[100];
    is.read(&tmp[0], sizeof(tmp));
    book.id = tmp ;
    is.read(&tmp[0], sizeof(tmp));
    book.serialNo = tmp ;
    is.read(&tmp[0], sizeof(tmp));
    book.title = tmp ;
    is.read(&tmp[0], sizeof(tmp));
    book.author = tmp ;
    is.read(&tmp[0], sizeof(tmp));
    book.publisher = tmp ;
    is.read(&tmp[0], sizeof(tmp));
    book.price = atoi(tmp);
    return is;
    
}


BOOK::BOOK(string id, string serialNo, string title, string author, string publisher, float price)
{
    this->id = id;
    this->serialNo = serialNo;
    this->title = title;
    this->author = author;
    this->publisher = publisher;
    this->price = price;
}
void BOOK::display()
{
    cout << "-----------------------------------" << endl;
    cout << "ID : " << id << "   Serial No : " << serialNo << endl;
    cout << "Title : " << title << endl;
    cout << "Author : " << author << endl;
    cout << "Publisher : " << publisher << endl;
    cout << "Price : " << price << " INR" << endl;
    cout << "-----------------------------------" << endl;
}
bool BOOK::isSameBook(string id, string serialNo)
{
    if (id == this->id && serialNo == this->serialNo)
    {
        return true;
    }
    return false;
}


// Member
class MEMBER
{
protected:
    string id;
    string name;
    string email;
    string address;

public:
    MEMBER() {}
    MEMBER(string id, string name, string email, string address)
    {
        this->id = id;
        this->name = name;
        this->email = email;
        this->address = address;
    }
    string get_id() { return id; }
    int return_max_issuable_book(){
        return 0;
    }
    friend ostream& operator<<(ostream& os, const MEMBER& member){
        char tmp[100];
        strcpy(tmp, member.id.c_str());
        os.write(tmp, sizeof(tmp));
        strcpy(tmp, member.name.c_str());
        os.write(tmp, sizeof(tmp));
        strcpy(tmp, member.email.c_str());
        os.write(tmp, sizeof(tmp));
        strcpy(tmp, member.address.c_str());
        os.write(tmp, sizeof(tmp));
        return os;
    }
    friend istream& operator>>(istream& is, MEMBER& member){
        char tmp[100];
        is.read(&tmp[0], sizeof(tmp));
        member.id = tmp ;
        is.read(&tmp[0], sizeof(tmp));
        member.name = tmp ;
        is.read(&tmp[0], sizeof(tmp));
        member.email = tmp ;
        is.read(&tmp[0], sizeof(tmp));
        member.address = tmp ;
        is.read(&tmp[0], sizeof(tmp));
        return is;
    }
};
class STUDENT:public MEMBER{
    public:
        STUDENT():MEMBER(){}
        STUDENT(string id, string name, string email, string address):MEMBER(id, name, email, address){}
        int return_max_issuable_book(){
            return ISSUE_LIMIT_STUDENT;
        }
        bool isFaculty(){return false;}
};
class FACULTY:public MEMBER{
    public:
        FACULTY():MEMBER(){}
        FACULTY(string id, string name, string email, string address):MEMBER(id, name, email, address){}
        int return_max_issuable_book(){
            return ISSUE_LIMIT_FACULTY;
        } 
        bool isFaculty(){return true;}
};


// Transaction
class TRANSACTION
{
private:
    string memberId;
    string bookId;
    string serialNo;
    string timeOfIssue;
    bool returned;

public:
    TRANSACTION() {}
    TRANSACTION(string memberId, string bookId, string serialNo);
    bool isIssuedToMember(string memberId);
    bool isBookIssued(string bookId, string serialNo);
    bool isSameTransaction(string memberId, string bookId, string serialNo);
    void markAsReturned() { returned = true; }
    void display();
    friend ostream& operator<<(ostream& os, const TRANSACTION& transaction);
    friend istream& operator>>(istream& is, TRANSACTION& transaction);
};

ostream& operator<<(ostream& os, const TRANSACTION& transaction){
    char tmp[100], flag[2];
    strcpy(tmp, transaction.memberId.c_str());
    os.write(tmp, sizeof(tmp));
    strcpy(tmp, transaction.bookId.c_str());
    os.write(tmp, sizeof(tmp));
    strcpy(tmp, transaction.serialNo.c_str());
    os.write(tmp, sizeof(tmp));
    strcpy(tmp, transaction.timeOfIssue.c_str());
    os.write(tmp, sizeof(tmp));
    snprintf(flag, sizeof(flag), "%d" , transaction.returned ? 1 : 0 );
    os.write(flag, sizeof(flag));
    return os;
}
istream& operator>>(istream& is, TRANSACTION& transaction){
    char tmp[100], flag[2];
    is.read(&tmp[0], sizeof(tmp));
    transaction.memberId = tmp;
    is.read(&tmp[0], sizeof(tmp));
    transaction.bookId = tmp;
    is.read(&tmp[0], sizeof(tmp));
    transaction.serialNo = tmp;
    is.read(&tmp[0], sizeof(tmp));
    transaction.timeOfIssue = tmp;
    is.read(&flag[0], sizeof(flag));
    int flagReturn = atoi(flag);
    transaction.returned = flagReturn == 1 ? true : false;
    return is;
}

TRANSACTION::TRANSACTION(string memberId, string bookId, string serialNo)
{
    this->memberId = memberId;
    this->bookId = bookId;
    this->serialNo = serialNo;
    this->returned = false;
    time_t now = time(0);
    timeOfIssue = ctime(&now);
}
bool TRANSACTION::isIssuedToMember(string memberId)
{
    if (returned)
        return false;
    return (memberId == this->memberId);
}
bool TRANSACTION::isBookIssued(string bookId, string serialNo)
{
    if (returned)
        return false;
    return (this->bookId == bookId && this->serialNo == serialNo);
}
bool TRANSACTION::isSameTransaction(string memberId, string bookId, string serialNo)
{
    return this->memberId == memberId && this->bookId == bookId && this->serialNo == serialNo;
}
void TRANSACTION::display()
{
    cout << "-----------------------------------" << endl;
    cout << "Member id : " << memberId << endl;
    cout << "Book id : " << bookId << endl;
    cout << "Serial no : " << serialNo << endl;
    cout << "Returned : ";
    if (returned)
        cout << "Yes";
    else
        cout << "No";
    cout << "\n-----------------------------------" << endl;
}


// Book List
class BOOKLIST{
    private:
        BOOK booksList[100];
        int no_of_books;
        string filename = "books.txt";
    public:
        BOOKLIST(){
            no_of_books = 0;
            restore();
        }
        int getNoOfBooks() { return no_of_books; }
        BOOK *getBook(int index) { return &booksList[index]; }
        void add(BOOK book){
            booksList[no_of_books++] = book;
            fstream file;
            file.open(filename, ios::app|ios::binary);
            file << book;
            file.close();
        }
        void restore();
};
void BOOKLIST::restore(){
    ifstream file1;
    file1.open(filename, ios::in|ios::binary);
    if(!file1.is_open()) return;
    file1.seekg (0, ios::beg);
    while (!file1.eof())
    {
        BOOK book;
        file1 >> book;
        if(file1.eof()) break;
        booksList[no_of_books++] = book;
        
    }
    file1.close();
}

// Student List
class STUDENTMEMBERLIST{
    private:
        STUDENT studentsList[100];
        int no_of_students;
        string filename = "students.txt";
    public:
    STUDENTMEMBERLIST(){
        no_of_students = 0;
        restore();
    }
    int getNoOfstudents(){ return no_of_students; }
    STUDENT *getMember(int index){ return &studentsList[index]; }
    void add(STUDENT student){
        studentsList[no_of_students++] = student;
        fstream file;
        file.open(filename, ios::app|ios::binary);
        file << student;
        file.close();
    }
    void restore(){
        ifstream file1;
        file1.open(filename, ios::in|ios::binary);
        if(!file1.is_open()) return;
        file1.seekg (0, ios::beg);
        while (!file1.eof())
        {
            STUDENT student;
            file1 >> student;
            cout << student.get_id() <<endl;
            studentsList[no_of_students++] = student;
        }
        file1.close();
    }
};
// Faculty List
class FACULTYMEMBERLIST{
    private:
        FACULTY membersList[100];
        int no_of_members;
        string filename = "faculties.txt";
    public:
    FACULTYMEMBERLIST(){
        no_of_members = 0;
        restore();
        for (int i = 0; i < no_of_members; i++)
        {
            membersList[i].get_id();
        }
        
    }
    int getNoOfmembers(){ return no_of_members; }
    FACULTY *getMember(int index){ return &membersList[index]; }
    void add(FACULTY faculty){
        membersList[no_of_members++] = faculty;
        fstream file;
        file.open(filename, ios::app|ios::binary);
        file << faculty;
        file.close();
    }
    void restore(){
        ifstream file1;
        file1.open(filename, ios::in|ios::binary);
        if(!file1.is_open()) return;
        file1.seekg (0, ios::beg);
        while (!file1.eof())
        {
            FACULTY faculty;
            file1 >> faculty;
            membersList[no_of_members++] = faculty;   
        }
        file1.close();
    }
};

// Transaction list
class TRANSACTIONLIST{
    private:
        TRANSACTION transactionList[100];
        int no_of_transactions;
        string filename = "transactions.txt";
    public:
        TRANSACTIONLIST(){
            no_of_transactions = 0;
            restore();
        }
        int getNoOfTransactions(){ return no_of_transactions; }
        TRANSACTION *getTransaction(int index){ return &transactionList[index]; }
        void add(TRANSACTION transaction){
            transactionList[no_of_transactions++] = transaction;
            fstream file;
            file.open(filename, ios::app|ios::binary);
            file << transaction;
            file.close();
        }
        void restore();
        void markAsReturnedTransaction(int index);
};

void TRANSACTIONLIST::restore(){
        ifstream file1;
        file1.open(filename, ios::in|ios::binary);
        if(!file1.is_open()) return;
        file1.seekg (0, ios::beg);
        while (!file1.eof())
        {
            TRANSACTION transaction;
            file1 >> transaction;
            if(file1.eof()) break;
            transactionList[no_of_transactions++] = transaction;
            
        }
        file1.close();
}
void TRANSACTIONLIST::markAsReturnedTransaction(int index){
    TRANSACTION transaction = transactionList[index];
    transaction.markAsReturned();
    fstream file;
    file.open(filename, ios::out|ios::in|ios::binary);
    cout << index << endl;
    file.seekp((sizeof(char[100])*4 + sizeof(char[2]))*index);
    file << transaction;
    file.close();
    transactionList[index] = transaction;
}


// Library 
class LIBRARY
{
private:
    BOOKLIST booklist;
    STUDENTMEMBERLIST studentList;
    FACULTYMEMBERLIST facultyList;
    TRANSACTIONLIST transactionList;
public:

    bool addBook(string id, string serialNo, string title, string author, string publisher, float price);
    int getNoOfBooksIssued(string memberId);
    bool isBookAvailable(string bookId, string serialNo);
    bool isEligibleForIssue(string memberId);
    bool addMember(string id, string name, string email, string address, bool isFaculty);
    string issueBook(string memberId, string bookId, string serialNo);
    string returnBook(string memberId, string bookId, string serialNo);
    void displayAllBooks();
    void displayAllTransactions();
};

int LIBRARY::getNoOfBooksIssued(string memberId)
{
    int count = 0;
    for (int i = 0; i < transactionList.getNoOfTransactions(); i++)
    {
        if (transactionList.getTransaction(i)->isIssuedToMember(memberId))
            count++;
    }
    return count;
}
bool LIBRARY::isBookAvailable(string bookId, string serialNo)
{
    for (int i = 0; i < transactionList.getNoOfTransactions(); i++)
    {
        if (transactionList.getTransaction(i)->isBookIssued(bookId, serialNo))
        {
            return false;
        }
    }
    return true;
}
bool LIBRARY::isEligibleForIssue(string memberId)
{
    STUDENT *student;
    FACULTY *faculty;
    bool isMemberFound = false;
    for (int i = 0; i < studentList.getNoOfstudents(); i++)
    {
        if (memberId == studentList.getMember(i)->get_id())
        {
            isMemberFound = true;
            student = studentList.getMember(i);
            // cout << student->return_max_issuable_book() << endl;
            // cout << getNoOfBooksIssued(memberId)  << endl;
            return (getNoOfBooksIssued(memberId) < student->return_max_issuable_book()) ? true : false;
        }
    }
    for (int i = 0; i < facultyList.getNoOfmembers(); i++)
    {
        if (memberId == facultyList.getMember(i)->get_id())
        {
            isMemberFound = true;
            faculty = facultyList.getMember(i);
            return (getNoOfBooksIssued(memberId) < faculty->return_max_issuable_book()) ? true : false;
        }
    }

    if (!isMemberFound)
        cout << "Member not found !" << endl;
    return false;
}
bool LIBRARY::addBook(string id, string serialNo, string title, string author, string publisher, float price)
{
    for (int i = 0; i < booklist.getNoOfBooks(); i++)
    {
        if (booklist.getBook(i)->isSameBook(id, serialNo))
        {
            return false;
        }
    }
    BOOK book(id, serialNo, title, author, publisher, price);
    booklist.add(book);
    return true;
}
bool LIBRARY::addMember(string id, string name, string email, string address, bool isFaculty)
{
    for (int i = 0; i < studentList.getNoOfstudents(); i++)
    {
        if (studentList.getMember(i)->get_id() == id)
        {
            return false;
        }
    }
    for (int i = 0; i < facultyList.getNoOfmembers(); i++)
    {
        if (facultyList.getMember(i)->get_id() == id)
        {
            return false;
        }
    }
    if(isFaculty){
        facultyList.add(FACULTY(id, name, email, address));
    }else{
        studentList.add(STUDENT(id, name, email, address));
    }
    return true;
}
string LIBRARY::issueBook(string memberId, string bookId, string serialNo)
{
    if (!isEligibleForIssue(memberId))
    {
        return "User not eligible for issuing new book!";
    }

    if (!isBookAvailable(bookId, serialNo))
    {
        return "Book not available in library for issue";
    }
    TRANSACTION trasnsaction(memberId, bookId, serialNo);
    transactionList.add(trasnsaction);
    return "Book issued successfully !";
}
string LIBRARY::returnBook(string memberId, string bookId, string serialNo)
{
    for (int i = 0; i < transactionList.getNoOfTransactions(); i++)
    {
        if (transactionList.getTransaction(i)->isSameTransaction(memberId, bookId, serialNo))
        {
            transactionList.markAsReturnedTransaction(i);
            return "Book returned successfully !";
        }
    }
    return "Book return failed !";
}
void LIBRARY::displayAllBooks()
{
    for (int i = 0; i < booklist.getNoOfBooks(); i++)
    {
        booklist.getBook(i)->display();
    }
};
void LIBRARY::displayAllTransactions()
{
    for (int i = 0; i < transactionList.getNoOfTransactions(); i++)
    {
        transactionList.getTransaction(i)->display();
        cout << endl;
    }
};




// Helper functions
void addBook(LIBRARY *library)
{
    string id, serialNo, title, author, publisher;
    float price;
    cout << "Enter id of book : ";
    cin >> id;
    cout << "Enter serial no of book : ";
    cin >> serialNo;
    cout << "Enter name of the book : ";
    cin >> title;
    cout << "Enter author of the book : ";
    cin >> author;
    cout << "Enter publisher of the book : ";
    cin >> publisher;
    cout << "Enter price of the book : ";
    cin >> price;

    bool success = library->addBook(id, serialNo, title, author, publisher, price);
    if (success)
        cout << "Book added successfully !" << endl;
    else
        cout << "Already the book exists with same id and serialno" << endl;
}
void addMember(LIBRARY *library)
{
    string id, name, email, address;
    char isFacultyChoice;
    bool isFaculty;
    cout << "Enter id of member : ";
    cin >> id;
    cout << "Enter name of the member : ";
    cin >> name;
    cout << "Enter email : ";
    cin >> email;
    cout << "Enter address : ";
    cin >> email;
    cout << "Are you a faculty member (y/n) : ";
    cin >> isFacultyChoice;
    isFacultyChoice == 'y' ? isFaculty = true : isFaculty = false;
    bool success = library->addMember(id, name, email, address, isFaculty);
    if (success)
        cout << "Member added successfully !" << endl;
    else
        cout << "Member bearing same id already exists " << endl;
}
void issueBook(LIBRARY *library)
{
    string memberId, bookId, serialNo;
    cout << "Enter id of member : ";
    cin >> memberId;
    cout << "Enter id of book : ";
    cin >> bookId;
    cout << "Enter serial no of book : ";
    cin >> serialNo;
    string response = library->issueBook(memberId, bookId, serialNo);
    cout << response;
}
void returnBook(LIBRARY *library)
{
    string memberId, bookId, serialNo;
    cout << "Enter id of member : ";
    cin >> memberId;
    cout << "Enter id of book : ";
    cin >> bookId;
    cout << "Enter serial no of book : ";
    cin >> serialNo;
    string response = library->returnBook(memberId, bookId, serialNo);
    cout << response;
}



int main()
{
    int choice;
    LIBRARY library;
    while (true)
    {
        cout << "\nSelect option from the menu" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display all books" << endl;
        cout << "3. Add member" << endl;
        cout << "4. Issue book" << endl;
        cout << "5. Return book" << endl;
        cout << "6. List all transactions" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook(&library);
            break;

        case 2:
            library.displayAllBooks();
            break;
        case 3:
            addMember(&library);
            break;
        case 4:
            issueBook(&library);
            break;
        case 5:
            returnBook(&library);
            break;
        case 6:
            library.displayAllTransactions();
            break;
        case 7:
            exit(0);
            break;
        default:
            cout << "Invalid choice ! Please retry" << endl;
            break;
        }
    }
    return 0;
}