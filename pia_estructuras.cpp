// pia_estructuras.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "pia_estructuras.h"
#include "Resource.h"
#include <fstream>
#include <string.h>
#include <commctrl.h>
#include <commdlg.h>

#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    PrincipalCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 
LRESULT CALLBACK ListaUsuariosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ListaVuelosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK RegistroAdminCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool menu(int opcion, HWND ventana);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PIAESTRUCTURAS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PIAESTRUCTURAS));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PIAESTRUCTURAS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PIAESTRUCTURAS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_LOGIN), NULL, WndProc);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
            switch (wmId)
            {
            case IDC_LOGOK: {
                HWND ventana =
                    CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback);
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }break;
            case IDC_REGISTROADMIN: {  
                HWND ventana =
                    CreateDialog(hInst, MAKEINTRESOURCE(IDD_REGISTRARADMIN), hWnd, RegistroAdminCallback); 
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }break;
            case IDM_EXIT: {
                DestroyWindow(hWnd);
                break;
            }default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Agregar cualquier código de dibujo que use hDC aquí...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK PrincipalCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        /*if (menu(wmId, hWnd)) {
            return FALSE;
        }*/
        switch (wmId) {
        case IDC_P1: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAUSUARIOS), hWnd, ListaUsuariosCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);

        }break;
        case IDC_P2: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAVUELOS), hWnd, ListaVuelosCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
            break;

        }
        }
    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }
     
    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
   
    }
    return FALSE;
}

LRESULT CALLBACK ListaUsuariosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {

        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE();
}

LRESULT ListaVuelosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {

        }
    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return FALSE();
}

LRESULT RegistroCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {

        }
    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return FALSE();
}

LRESULT RegistroAdminCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case ID_AGREGARAdm: {
            int res = MessageBox(hWnd, L"ADMINISTRADOR REGISTRADO", L"REGISTRADO", MB_OKCANCEL | MB_ICONASTERISK);

            if (res == IDOK)
            {
                HWND ventana =
                    CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback);
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }
        }
        }
    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return FALSE();
}