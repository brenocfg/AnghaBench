#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct security_priv {int dot11PrivacyKeyIndex; TYPE_1__* dot11DefKey; int /*<<< orphan*/ * dot11DefKeylen; int /*<<< orphan*/  dot11PrivacyAlgrthm; } ;
struct ndis_802_11_wep {int KeyIndex; int /*<<< orphan*/  KeyLength; int /*<<< orphan*/  KeyMaterial; } ;
struct adapter {struct security_priv securitypriv; } ;
struct TYPE_2__ {int /*<<< orphan*/ * skey; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 int /*<<< orphan*/  _NO_PRIVACY_ ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _WEP104_ ; 
 int /*<<< orphan*/  _WEP40_ ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_set_c_ ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rtw_set_key (struct adapter*,struct security_priv*,int,int) ; 

u8 rtw_set_802_11_add_wep(struct adapter *padapter, struct ndis_802_11_wep *wep)
{
	int keyid, res;
	struct security_priv *psecuritypriv = &padapter->securitypriv;
	u8 ret = _SUCCESS;

	keyid = wep->KeyIndex & 0x3fffffff;

	if (keyid >= 4) {
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("MgntActrtw_set_802_11_add_wep:keyid>4 =>fail\n"));
		ret = false;
		goto exit;
	}

	switch (wep->KeyLength) {
	case 5:
		psecuritypriv->dot11PrivacyAlgrthm = _WEP40_;
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("MgntActrtw_set_802_11_add_wep:wep->KeyLength = 5\n"));
		break;
	case 13:
		psecuritypriv->dot11PrivacyAlgrthm = _WEP104_;
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("MgntActrtw_set_802_11_add_wep:wep->KeyLength = 13\n"));
		break;
	default:
		psecuritypriv->dot11PrivacyAlgrthm = _NO_PRIVACY_;
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("MgntActrtw_set_802_11_add_wep:wep->KeyLength!= 5 or 13\n"));
		break;
	}
	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_,
		 ("rtw_set_802_11_add_wep:before memcpy, wep->KeyLength = 0x%x wep->KeyIndex = 0x%x  keyid =%x\n",
		 wep->KeyLength, wep->KeyIndex, keyid));

	memcpy(&psecuritypriv->dot11DefKey[keyid].skey[0],
	       &wep->KeyMaterial, wep->KeyLength);

	psecuritypriv->dot11DefKeylen[keyid] = wep->KeyLength;

	psecuritypriv->dot11PrivacyKeyIndex = keyid;

	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_,
		 ("rtw_set_802_11_add_wep:security key material : %x %x %x %x %x %x %x %x %x %x %x %x %x\n",
		 psecuritypriv->dot11DefKey[keyid].skey[0],
		 psecuritypriv->dot11DefKey[keyid].skey[1],
		 psecuritypriv->dot11DefKey[keyid].skey[2],
		 psecuritypriv->dot11DefKey[keyid].skey[3],
		 psecuritypriv->dot11DefKey[keyid].skey[4],
		 psecuritypriv->dot11DefKey[keyid].skey[5],
		 psecuritypriv->dot11DefKey[keyid].skey[6],
		 psecuritypriv->dot11DefKey[keyid].skey[7],
		 psecuritypriv->dot11DefKey[keyid].skey[8],
		 psecuritypriv->dot11DefKey[keyid].skey[9],
		 psecuritypriv->dot11DefKey[keyid].skey[10],
		 psecuritypriv->dot11DefKey[keyid].skey[11],
		 psecuritypriv->dot11DefKey[keyid].skey[12]));

	res = rtw_set_key(padapter, psecuritypriv, keyid, 1);

	if (res == _FAIL)
		ret = false;
exit:
	return ret;
}