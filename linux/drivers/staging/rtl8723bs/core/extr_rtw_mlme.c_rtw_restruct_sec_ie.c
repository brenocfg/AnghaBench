#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  scalar_t__ u8 ;
struct security_priv {scalar_t__ ndisauthtype; scalar_t__* wps_ie; int wps_ie_len; scalar_t__* supplicant_ie; } ;
struct mlme_priv {int /*<<< orphan*/  assoc_bssid; } ;
struct adapter {struct security_priv securitypriv; struct mlme_priv mlmepriv; } ;
typedef  scalar_t__ sint ;

/* Variables and functions */
 scalar_t__ Ndis802_11AuthModeWPA ; 
 scalar_t__ Ndis802_11AuthModeWPA2 ; 
 scalar_t__ Ndis802_11AuthModeWPA2PSK ; 
 scalar_t__ Ndis802_11AuthModeWPAPSK ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int SecIsInPMKIDList (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_UNDER_WPS ; 
 scalar_t__ _WPA2_IE_ID_ ; 
 scalar_t__ _WPA_IE_ID_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ rtw_append_pmkid (struct adapter*,int,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_report_sec_ie (struct adapter*,scalar_t__,int*) ; 

sint rtw_restruct_sec_ie(struct adapter *adapter, u8 *in_ie, u8 *out_ie, uint in_len)
{
	u8 authmode = 0x0;
	uint	ielength;
	int iEntry;

	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
	struct security_priv *psecuritypriv = &adapter->securitypriv;
	uint	ndisauthmode = psecuritypriv->ndisauthtype;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_,
		 ("+rtw_restruct_sec_ie: ndisauthmode =%d\n", ndisauthmode));

	/* copy fixed ie only */
	memcpy(out_ie, in_ie, 12);
	ielength = 12;
	if ((ndisauthmode == Ndis802_11AuthModeWPA) || (ndisauthmode == Ndis802_11AuthModeWPAPSK))
			authmode = _WPA_IE_ID_;
	if ((ndisauthmode == Ndis802_11AuthModeWPA2) || (ndisauthmode == Ndis802_11AuthModeWPA2PSK))
			authmode = _WPA2_IE_ID_;

	if (check_fwstate(pmlmepriv, WIFI_UNDER_WPS)) {
		memcpy(out_ie+ielength, psecuritypriv->wps_ie, psecuritypriv->wps_ie_len);

		ielength += psecuritypriv->wps_ie_len;
	} else if ((authmode == _WPA_IE_ID_) || (authmode == _WPA2_IE_ID_)) {
		/* copy RSN or SSN */
		memcpy(&out_ie[ielength], &psecuritypriv->supplicant_ie[0], psecuritypriv->supplicant_ie[1]+2);
		/* debug for CONFIG_IEEE80211W
		{
			int jj;
			printk("supplicant_ie_length =%d &&&&&&&&&&&&&&&&&&&\n", psecuritypriv->supplicant_ie[1]+2);
			for (jj = 0; jj < psecuritypriv->supplicant_ie[1]+2; jj++)
				printk(" %02x ", psecuritypriv->supplicant_ie[jj]);
			printk("\n");
		}*/
		ielength += psecuritypriv->supplicant_ie[1]+2;
		rtw_report_sec_ie(adapter, authmode, psecuritypriv->supplicant_ie);
	}

	iEntry = SecIsInPMKIDList(adapter, pmlmepriv->assoc_bssid);
	if (iEntry < 0) {
		return ielength;
	} else {
		if (authmode == _WPA2_IE_ID_)
			ielength = rtw_append_pmkid(adapter, iEntry, out_ie, ielength);
	}
	return ielength;
}