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
typedef  unsigned short u16 ;
struct TYPE_2__ {int AuthAlgrthm; int wps_phase; int wps_ie_len; int /*<<< orphan*/  wps_ie; void* ndisencryptstatus; void* PrivacyAlgrthm; void* XGrpPrivacy; int /*<<< orphan*/  ndisauthtype; } ;
struct _adapter {int /*<<< orphan*/  pnetdev; TYPE_1__ securitypriv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned short MAX_WPA_IE_LEN ; 
 int /*<<< orphan*/  Ndis802_11AuthModeWPA2PSK ; 
 int /*<<< orphan*/  Ndis802_11AuthModeWPAPSK ; 
 void* Ndis802_11Encryption1Enabled ; 
 void* Ndis802_11Encryption2Enabled ; 
 void* Ndis802_11Encryption3Enabled ; 
 void* Ndis802_11EncryptionDisabled ; 
 unsigned short RSN_HEADER_LEN ; 
#define  WPA_CIPHER_CCMP 132 
#define  WPA_CIPHER_NONE 131 
#define  WPA_CIPHER_TKIP 130 
#define  WPA_CIPHER_WEP104 129 
#define  WPA_CIPHER_WEP40 128 
 void* _AES_ ; 
 void* _NO_PRIVACY_ ; 
 void* _TKIP_ ; 
 int _VENDOR_SPECIFIC_IE_ ; 
 void* _WEP104_ ; 
 void* _WEP40_ ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmemdup (char*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ r8712_parse_wpa2_ie (int*,unsigned short,int*,int*) ; 
 scalar_t__ r8712_parse_wpa_ie (int*,unsigned short,int*,int*) ; 

__attribute__((used)) static int r871x_set_wpa_ie(struct _adapter *padapter, char *pie,
			    unsigned short ielen)
{
	u8 *buf = NULL;
	int group_cipher = 0, pairwise_cipher = 0;
	int ret = 0;

	if ((ielen > MAX_WPA_IE_LEN) || (pie == NULL))
		return -EINVAL;
	if (ielen) {
		buf = kmemdup(pie, ielen, GFP_ATOMIC);
		if (buf == NULL)
			return -ENOMEM;
		if (ielen < RSN_HEADER_LEN) {
			ret  = -EINVAL;
			goto exit;
		}
		if (r8712_parse_wpa_ie(buf, ielen, &group_cipher,
		    &pairwise_cipher) == 0) {
			padapter->securitypriv.AuthAlgrthm = 2;
			padapter->securitypriv.ndisauthtype =
				  Ndis802_11AuthModeWPAPSK;
		}
		if (r8712_parse_wpa2_ie(buf, ielen, &group_cipher,
		    &pairwise_cipher) == 0) {
			padapter->securitypriv.AuthAlgrthm = 2;
			padapter->securitypriv.ndisauthtype =
				  Ndis802_11AuthModeWPA2PSK;
		}
		switch (group_cipher) {
		case WPA_CIPHER_NONE:
			padapter->securitypriv.XGrpPrivacy =
				 _NO_PRIVACY_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11EncryptionDisabled;
			break;
		case WPA_CIPHER_WEP40:
			padapter->securitypriv.XGrpPrivacy = _WEP40_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption1Enabled;
			break;
		case WPA_CIPHER_TKIP:
			padapter->securitypriv.XGrpPrivacy = _TKIP_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption2Enabled;
			break;
		case WPA_CIPHER_CCMP:
			padapter->securitypriv.XGrpPrivacy = _AES_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption3Enabled;
			break;
		case WPA_CIPHER_WEP104:
			padapter->securitypriv.XGrpPrivacy = _WEP104_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption1Enabled;
			break;
		}
		switch (pairwise_cipher) {
		case WPA_CIPHER_NONE:
			padapter->securitypriv.PrivacyAlgrthm =
				 _NO_PRIVACY_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11EncryptionDisabled;
			break;
		case WPA_CIPHER_WEP40:
			padapter->securitypriv.PrivacyAlgrthm = _WEP40_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption1Enabled;
			break;
		case WPA_CIPHER_TKIP:
			padapter->securitypriv.PrivacyAlgrthm = _TKIP_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption2Enabled;
			break;
		case WPA_CIPHER_CCMP:
			padapter->securitypriv.PrivacyAlgrthm = _AES_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption3Enabled;
			break;
		case WPA_CIPHER_WEP104:
			padapter->securitypriv.PrivacyAlgrthm = _WEP104_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption1Enabled;
			break;
		}
		padapter->securitypriv.wps_phase = false;
		{/* set wps_ie */
			u16 cnt = 0;
			u8 eid, wps_oui[4] = {0x0, 0x50, 0xf2, 0x04};

			while (cnt < ielen) {
				eid = buf[cnt];

				if ((eid == _VENDOR_SPECIFIC_IE_) &&
				    (!memcmp(&buf[cnt + 2], wps_oui, 4))) {
					netdev_info(padapter->pnetdev, "r8712u: SET WPS_IE\n");
					padapter->securitypriv.wps_ie_len =
					    ((buf[cnt + 1] + 2) <
					    (MAX_WPA_IE_LEN << 2)) ?
					    (buf[cnt + 1] + 2) :
					    (MAX_WPA_IE_LEN << 2);
					memcpy(padapter->securitypriv.wps_ie,
					    &buf[cnt],
					    padapter->securitypriv.wps_ie_len);
					padapter->securitypriv.wps_phase =
								 true;
					netdev_info(padapter->pnetdev, "r8712u: SET WPS_IE, wps_phase==true\n");
					cnt += buf[cnt + 1] + 2;
					break;
				}

				cnt += buf[cnt + 1] + 2;
			}
		}
	}
exit:
	kfree(buf);
	return ret;
}