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
union iwreq_data {int /*<<< orphan*/  param; } ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; } ;
struct TYPE_2__ {int btkip_countermeasure; int /*<<< orphan*/  ndisauthtype; int /*<<< orphan*/  AuthAlgrthm; void* XGrpPrivacy; void* PrivacyAlgrthm; int /*<<< orphan*/  ndisencryptstatus; } ;
struct _adapter {TYPE_1__ securitypriv; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IW_AUTH_80211_AUTH_ALG 137 
#define  IW_AUTH_CIPHER_GROUP 136 
#define  IW_AUTH_CIPHER_PAIRWISE 135 
#define  IW_AUTH_DROP_UNENCRYPTED 134 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 133 
#define  IW_AUTH_PRIVACY_INVOKED 132 
#define  IW_AUTH_RX_UNENCRYPTED_EAPOL 131 
#define  IW_AUTH_TKIP_COUNTERMEASURES 130 
#define  IW_AUTH_WPA_ENABLED 129 
#define  IW_AUTH_WPA_VERSION 128 
 int /*<<< orphan*/  Ndis802_11AuthModeOpen ; 
 int /*<<< orphan*/  Ndis802_11Encryption1Enabled ; 
 int /*<<< orphan*/  Ndis802_11EncryptionDisabled ; 
 void* _NO_PRIVACY_ ; 
 struct _adapter* netdev_priv (struct net_device*) ; 
 int wpa_set_auth_algs (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r871x_wx_set_auth(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct _adapter *padapter = netdev_priv(dev);
	struct iw_param *param = (struct iw_param *)&(wrqu->param);
	int paramid;
	int paramval;
	int ret = 0;

	paramid = param->flags & IW_AUTH_INDEX;
	paramval = param->value;
	switch (paramid) {
	case IW_AUTH_WPA_VERSION:
		break;
	case IW_AUTH_CIPHER_PAIRWISE:
		break;
	case IW_AUTH_CIPHER_GROUP:
		break;
	case IW_AUTH_KEY_MGMT:
		/*
		 *  ??? does not use these parameters
		 */
		break;
	case IW_AUTH_TKIP_COUNTERMEASURES:
		if (paramval) {
			/* wpa_supplicant is enabling tkip countermeasure. */
			padapter->securitypriv.btkip_countermeasure = true;
		} else {
			/* wpa_supplicant is disabling tkip countermeasure. */
			padapter->securitypriv.btkip_countermeasure = false;
		}
		break;
	case IW_AUTH_DROP_UNENCRYPTED:
		/* HACK:
		 *
		 * wpa_supplicant calls set_wpa_enabled when the driver
		 * is loaded and unloaded, regardless of if WPA is being
		 * used.  No other calls are made which can be used to
		 * determine if encryption will be used or not prior to
		 * association being expected.  If encryption is not being
		 * used, drop_unencrypted is set to false, else true -- we
		 * can use this to determine if the CAP_PRIVACY_ON bit should
		 * be set.
		 */
		if (padapter->securitypriv.ndisencryptstatus ==
		    Ndis802_11Encryption1Enabled) {
			/* it means init value, or using wep,
			 * ndisencryptstatus =
			 *	Ndis802_11Encryption1Enabled,
			 * then it needn't reset it;
			 */
			break;
		}

		if (paramval) {
			padapter->securitypriv.ndisencryptstatus =
				   Ndis802_11EncryptionDisabled;
			padapter->securitypriv.PrivacyAlgrthm =
				  _NO_PRIVACY_;
			padapter->securitypriv.XGrpPrivacy =
				  _NO_PRIVACY_;
			padapter->securitypriv.AuthAlgrthm = 0;
			padapter->securitypriv.ndisauthtype =
				  Ndis802_11AuthModeOpen;
		}
		break;
	case IW_AUTH_80211_AUTH_ALG:
		ret = wpa_set_auth_algs(dev, (u32)paramval);
		break;
	case IW_AUTH_WPA_ENABLED:
		break;
	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
		break;
	case IW_AUTH_PRIVACY_INVOKED:
		break;
	default:
		return -EOPNOTSUPP;
	}

	return ret;
}