/****************************************************************************

Copyright (c) 2008-2020 Kevin Wu (Wu Feng)

github: https://github.com/kevinwu1024/ExtremeCopy
site: http://www.easersoft.com

Licensed under the Apache License, Version 2.0 License (the "License"); you may not use this file except
in compliance with the License. You may obtain a copy of the License at

https://opensource.org/licenses/Apache-2.0

****************************************************************************/

#include "StdAfx.h"
#include "AboutDlg.h"
#include "..\AppRegister.h"
#include "..\XCConfiguration.h"
#include "..\Language\XCRes_ENU\resource.h"

CAboutDlg::CAboutDlg(int nDlgID):CptDialog(nDlgID,NULL,CptMultipleLanguage::GetInstance()->GetResourceHandle())
{
}

CAboutDlg::~CAboutDlg(void)
{
}

BOOL CAboutDlg::OnInitDialog() 
{
	this->CenterScreen() ;

	m_CancelSkinButton.Attach(this->GetDlgItem(IDCANCEL)) ;

	CptString strAbout = CptMultipleLanguage::GetInstance()->GetString(IDS_TITLE_ABOUT) ;
	::SetWindowText(this->GetSafeHwnd(),strAbout.c_str()) ;

	CptString strVersion = ::MakeXCVersionString() ;

	if(strVersion.GetLength()>0)
	{
		this->SetDlgItemText(IDC_STATIC_ABOUTVERSION,strVersion.c_str()) ;

		HYPERLINKSTRUCT hls = {0};

		hls.bBold     = false;				// Bold font?
		hls.bUnderline = true;				// Underlined font?
		hls.bUseBg    = false;				// Use opaque background?
		hls.bUseCursor = true;				// Use custom cursor?
		hls.hCursor    = CXCConfiguration::GetInstance()->GetGlobalData()->hCursorHand ;//::LoadCursor( GetModuleHandle( NULL ), (LPCTSTR)IDC_CURSOR_HAND );
		hls.clrBack   = RGB(0,0,0);			// Fill this out if bUseBg is true
		hls.clrHilite = RGB( 0, 0, 255 );	// Color of mouseover font
		hls.clrText   = RGB( 0, 0, 255 );	// Color of regular font
		hls.coordX    = 76;					// X-axis coordinate of upper left corner
		hls.coordY    = 55;					// Y-axis coordinate of upper left corner
		hls.ctlID     = 0;					// Set this to use GetDlgItem on this control
		hls.fontsize  = 15;					// Size of font used
		hls.height    = 20;					// Height of control
		hls.hWndParent = this->GetSafeHwnd();              // Handle to parent window
		hls.pFn       = OnHyperLinkHomePageCallBack2;		// Function pointer to function that is called when link is clicked
		hls.pCBAgr = (void*)WEBLINK_SITE_HOME ;
		hls.szCaption = LINK_HOME_WEBSITE; // Caption
		hls.szFontName = _T("Arial");			// Font face name
		hls.width      = 130;				// Width of control

		m_Hyperlink.Create(&hls) ;
	}

	{
		HYPERLINKSTRUCT hls = {0};

		hls.bBold     = false;				// Bold font?
		hls.bUnderline = true;				// Underlined font?
		hls.bUseBg    = false;				// Use opaque background?
		hls.bUseCursor = true;				// Use custom cursor?
		hls.hCursor    = CXCConfiguration::GetInstance()->GetGlobalData()->hCursorHand ;//::LoadCursor( GetModuleHandle( NULL ), (LPCTSTR)IDC_CURSOR_HAND );
		hls.clrBack   = RGB(0,0,0);			// Fill this out if bUseBg is true
		hls.clrHilite = RGB( 0, 0, 255 );	// Color of mouseover font
		hls.clrText   = RGB( 0, 0, 255 );	// Color of regular font
		hls.coordX    = 76;					// X-axis coordinate of upper left corner
		hls.coordY    = 87;					// Y-axis coordinate of upper left corner
		hls.ctlID     = IDC_STATIC_EMAIL;	// Set this to use GetDlgItem on this control
		hls.fontsize  = 15;					// Size of font used
		hls.height    = 20;					// Height of control
		hls.hWndParent = this->GetSafeHwnd();              // Handle to parent window
		hls.pFn       = OnHyperLinkHomePageCallBack2;		// Function pointer to function that is called when link is clicked
		hls.pCBAgr = (void*)WEBLINK_EMAIL_SUPPORT ;
		hls.szCaption = LINK_EMAIL_SUPPORT; // Caption
		hls.szFontName = _T("Arial");			// Font face name
		hls.width      = 140;				// Width of control

		m_EmailHyperlink.Create(&hls) ;
	}
	
	const TCHAR* pAllRight = _T("© 2020 All right reserved.") ;
	
#ifdef VERSION_CHECKREGSITER
	CAppRegister reg ;

	m_bReg = reg.IsAppRegistedReadOnly() ;

	CptString strTxt ;

	if(m_bReg)
	{
		strTxt = ::CptMultipleLanguage::GetInstance()->GetString(IDS_ABOUT_ALREADYREGESITER) ;
	}
	else
	{
		strTxt = ::CptMultipleLanguage::GetInstance()->GetString(IDS_ABOUT_UNREGISTER) ;
	}

	this->SetDlgItemText(IDC_STATIC_REGIST,strTxt.c_str()) ;
#else
	

	CptString strTxt = ::CptMultipleLanguage::GetInstance()->GetString(IDS_ABOUT_FREEFORHOMEUSER) ;
	this->SetDlgItemText(IDC_STATIC_REGIST,strTxt.c_str()) ;

	this->SetDlgItemText(IDC_STATIC_REGIST,_T("")) ;

#endif

	this->SetDlgItemText(IDC_STATIC_ALLRIGHT,pAllRight) ;

	return CptDialog::OnInitDialog() ;

}

void CAboutDlg::OnPaint() 
{
	CptDialog::OnPaint() ;

	m_CloseSkinButton.Update() ;
}

void CAboutDlg::OnButtonClick(int nButtonID) 
{
	switch(nButtonID)
	{
//	case IDC_BUTTON_TITLECLOSE: // 退出
	case IDC_BUTTON_EXIT:
		this->PerformButton(IDCANCEL) ;
		break ;
	}
}

int CAboutDlg::OnProcessMessage(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch(uMsg)
	{
	case WM_CTLCOLORBTN :
	case WM_CTLCOLOREDIT :
	case WM_CTLCOLORDLG :
	case WM_CTLCOLORSTATIC :
	case WM_CTLCOLORSCROLLBAR :
	case WM_CTLCOLORLISTBOX :
		{
			HDC hdc = (HDC)wParam ;

			::SetBkMode(hdc,TRANSPARENT) ;
			if(uMsg==WM_CTLCOLORSTATIC)
			{
				if((HWND)lParam==this->GetDlgItem(IDC_STATIC_REGIST))
				{//
					if(m_bReg)
					{
						::SetTextColor(hdc,RGB(0,0,0)) ;
					}
					else
					{
						::SetTextColor(hdc,RGB(250,0,0)) ;
					}
				}
				else
				{
					//::SetTextColor(hdc,RGB(10,10,230)) ;
				}
				
			}

			return (int)::GetSysColorBrush(COLOR_BTNFACE) ;
			//return (int)::GetStockObject(NULL_BRUSH) ;
			//return (int)CXCConfiguration::GetInstance()->GetGlobalData()->hDlgBkBrush ;
		}
		break ;
	}

	return CptDialog::OnProcessMessage(hWnd,uMsg,wParam,lParam) ;
}