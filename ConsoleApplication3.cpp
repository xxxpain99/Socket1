#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <WS2tcpip.h>
#include <list>
#include <vector>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

//SOCKET

struct Bill {
    int Client;
    double Balance;
};



struct Client {
    SOCKET Socket;
    int ID;

    Client(SOCKET s, int id) {
        Socket = s;
        ID = id;
    }
};

enum OPERATIONS {
    OPEN,
    CLOSE,
    UP,
    DOWN
};

struct Data {
    int UserID;
    double value;
    OPERATIONS Operations;
};

list<Client*> ClientList;

void Run(Client*);

int main()
{
   
    WSADATA data;
    int e = WSAStartup(MAKEWORD(2, 2), &data);
    if (e != 0)
    {
        cout << "data has destroyed and annihilation\n";
        return 1;
    }
    SOCKET serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket < 0)
    {
        cout << "server has destroyed\n";
        return 1;
    }
    struct sockaddr_in serverAddress;
    memset((&serverAddress), 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.S_un.S_un_b.s_b1 = 127;
    serverAddress.sin_addr.S_un.S_un_b.s_b2 = 0;
    serverAddress.sin_addr.S_un.S_un_b.s_b3 = 0;
    serverAddress.sin_addr.S_un.S_un_b.s_b4 = 1;


    int result = bind(serverSocket,
        (const sockaddr*)(&serverAddress),
        sizeof(serverAddress));

    if (result == SOCKET_ERROR)
    {
        std::cout << "bind socket error" << std::endl;
        return 1;
    }



    result = listen(serverSocket, 100);
    if (result < 0)
    {
        std::cout << "listen socket error" << std::endl;
        return 1;
    }
    int id = 1;
    while (true)
    {
        std::cout << "wait client connection\n";
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        std::cout << "client connected\n";
        Client* client = new Client(clientSocket, id++);
        new thread(Run, client);
        ClientList.push_back(client);
    }
    return 0;
}

void Run(Client* client) {
    int n = 0;
    Data recvData;

    while (true)
    {
        n = recv(client->Socket, (char*)(&recvData), sizeof(recvData), 0);
        if (n < 0)
        {
            return;
        }
        switch (recvData.Operations)
        {
        case OPERATIONS::OPEN:


            break;

        case OPERATIONS::CLOSE:


            break;

        case OPERATIONS::UP:


            break;

        case OPERATIONS::DOWN:



            break;

        default:
            break;

        }
    }

    ClientList.remove(client);

}