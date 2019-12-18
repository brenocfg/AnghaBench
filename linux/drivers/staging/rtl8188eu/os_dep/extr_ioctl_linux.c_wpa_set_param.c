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
typedef  int /*<<< orphan*/  value ;
typedef  int uint ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ndisauthtype; int /*<<< orphan*/  ndisencryptstatus; int /*<<< orphan*/  dot11AuthAlgrthm; } ;
struct adapter {TYPE_1__ securitypriv; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IEEE_PARAM_AUTH_ALGS 134 
#define  IEEE_PARAM_DROP_UNENCRYPTED 133 
#define  IEEE_PARAM_IEEE_802_1X 132 
#define  IEEE_PARAM_PRIVACY_INVOKED 131 
#define  IEEE_PARAM_TKIP_COUNTERMEASURES 130 
#define  IEEE_PARAM_WPAX_SELECT 129 
#define  IEEE_PARAM_WPA_ENABLED 128 
 int /*<<< orphan*/  Ndis802_11AuthModeWPA2PSK ; 
 int /*<<< orphan*/  Ndis802_11AuthModeWPAPSK ; 
 int /*<<< orphan*/  Ndis802_11Encryption2Enabled ; 
 int /*<<< orphan*/  Ndis802_11Encryption3Enabled ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_os_c ; 
 int /*<<< orphan*/  dot11AuthAlgrthm_8021X ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int wpa_set_auth_algs (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_set_param(struct net_device *dev, u8 name, u32 value)
{
	uint ret = 0;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev);

	switch (name) {
	case IEEE_PARAM_WPA_ENABLED:
		padapter->securitypriv.dot11AuthAlgrthm = dot11AuthAlgrthm_8021X; /* 802.1x */
		switch ((value)&0xff) {
		case 1: /* WPA */
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPAPSK; /* WPA_PSK */
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption2Enabled;
			break;
		case 2: /* WPA2 */
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPA2PSK; /* WPA2_PSK */
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption3Enabled;
			break;
		}
		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_,
			 ("wpa_set_param:padapter->securitypriv.ndisauthtype =%d\n", padapter->securitypriv.ndisauthtype));
		break;
	case IEEE_PARAM_TKIP_COUNTERMEASURES:
		break;
	case IEEE_PARAM_DROP_UNENCRYPTED: {
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

		break;
	}
	case IEEE_PARAM_PRIVACY_INVOKED:
		break;

	case IEEE_PARAM_AUTH_ALGS:
		ret = wpa_set_auth_algs(dev, value);
		break;
	case IEEE_PARAM_IEEE_802_1X:
		break;
	case IEEE_PARAM_WPAX_SELECT:
		break;
	default:
		ret = -EOPNOTSUPP;
		break;
	}
	return ret;
}