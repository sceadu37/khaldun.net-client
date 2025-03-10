// dinput_dll.h

#ifndef __DINPUT_DLL_H
#define __DINPUT_DLL_H

#include "include/global.h"
#include "include/shared.h"

typedef long (__stdcall *DirectInputCreateA_fn)(HINSTANCE hinst, DWORD dwVersion, /* LPDIRECTINPUTA* */ LPVOID *lplpDirectInput, /* LPUNKNOWN */ LPVOID punkOuter);
DirectInputCreateA_fn oDirectInputCreateA = 0;
typedef long (__stdcall *DirectInputCreateEx_fn)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, /* LPUNKNOWN */ LPVOID punkOuter);
DirectInputCreateEx_fn oDirectInputCreateEx = 0;
typedef long (__stdcall *DirectInputCreateW_fn)(HINSTANCE hinst, DWORD dwVersion, /* LPDIRECTINPUTW* */ LPVOID *lplpDirectInput, /* LPUNKNOWN */ LPVOID punkOuter);
DirectInputCreateW_fn oDirectInputCreateW = 0;

long __stdcall p_DirectInputCreateA(HINSTANCE hinst, DWORD dwVersion, /* LPDIRECTINPUTA* */ LPVOID *lplpDirectInput, /* LPUNKNOWN */ LPVOID punkOuter) {
#pragma comment(linker, "/EXPORT:DirectInputCreateA=_p_DirectInputCreateA@16")

  if (!oDirectInputCreateA) {
    oDirectInputCreateA = GetSysProc(sDInput, "DirectInputCreateA");
    if (oDirectInputCreateA) {
      HMODULE hm;
      GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN, (LPCSTR)oDirectInputCreateA, &hm);
    } else {
      oDirectInputCreateA = (void*)-1;
    }
  }
  if (oDirectInputCreateA != (void*)-1)
    return oDirectInputCreateA(hinst, dwVersion, lplpDirectInput, punkOuter);

  return 0x80004005; // DIERR_GENERIC (E_FAIL)
}

long __stdcall p_DirectInputCreateEx(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, /* LPUNKNOWN */ LPVOID punkOuter) {
#pragma comment(linker, "/EXPORT:DirectInputCreateEx=_p_DirectInputCreateEx@20")

  if (!oDirectInputCreateEx) {
    oDirectInputCreateEx = GetSysProc(sDInput, "DirectInputCreateEx");
    if (oDirectInputCreateEx) {
      HMODULE hm;
      GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN, (LPCSTR)oDirectInputCreateEx, &hm);
    } else {
      oDirectInputCreateEx = (void*)-1;
    }
  }
  if (oDirectInputCreateEx != (void*)-1)
    return oDirectInputCreateEx(hinst, dwVersion, riidltf, ppvOut, punkOuter);

  return 0x80004005; // DIERR_GENERIC (E_FAIL)
}

long __stdcall p_DirectInputCreateW(HINSTANCE hinst, DWORD dwVersion, /* LPDIRECTINPUTW* */ LPVOID *lplpDirectInput, /* LPUNKNOWN */ LPVOID punkOuter) {
#pragma comment(linker, "/EXPORT:DirectInputCreateW=_p_DirectInputCreateW@16")

  if (!oDirectInputCreateW) {
    oDirectInputCreateW = GetSysProc(sDInput, "DirectInputCreateW");
    if (oDirectInputCreateW) {
      HMODULE hm;
      GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN, (LPCSTR)oDirectInputCreateW, &hm);
    } else {
      oDirectInputCreateW = (void*)-1;
    }
  }
  if (oDirectInputCreateW != (void*)-1)
    return oDirectInputCreateW(hinst, dwVersion, lplpDirectInput, punkOuter);

  return 0x80004005; // DIERR_GENERIC (E_FAIL)
}

__noinline static void dinput_hook() {
  pModName = sDInput;
#ifndef DLL_PROXY_DELAY_LOAD
  HMODULE hm = LoadSysMod(sDInput);
  if (hm) {
    oDirectInputCreateA = (DirectInputCreateA_fn)GetProcAddress(hm,"DirectInputCreateA");
    oDirectInputCreateEx = (DirectInputCreateEx_fn)GetProcAddress(hm,"DirectInputCreateEx");
    oDirectInputCreateW = (DirectInputCreateW_fn)GetProcAddress(hm,"DirectInputCreateW");
    oDllGetClassObject = (DllGetClassObject_fn)GetProcAddress(hm,"DllGetClassObject");
    oDllRegisterServer = (DllRegisterServer_fn)GetProcAddress(hm,"DllRegisterServer");
    oDllUnregisterServer = (DllUnregisterServer_fn)GetProcAddress(hm,"DllUnregisterServer");
    if (oDirectInputCreateA)
      GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN, (LPCSTR)oDirectInputCreateA, &hm);
  }
#endif // !DLL_PROXY_DELAY_LOAD
}

#endif // __DINPUT_DLL_H

