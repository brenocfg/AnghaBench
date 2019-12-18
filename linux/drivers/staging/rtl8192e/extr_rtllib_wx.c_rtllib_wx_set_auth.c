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
struct rtllib_device {int tkip_countermeasures; int drop_unencrypted; int open_wep; int auth_mode; int wpa_enabled; int ieee802_1x; int privacy_invoked; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  IW_AUTH_80211_AUTH_ALG 137 
 int IW_AUTH_ALG_LEAP ; 
 int IW_AUTH_ALG_OPEN_SYSTEM ; 
 int IW_AUTH_ALG_SHARED_KEY ; 
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

int rtllib_wx_set_auth(struct rtllib_device *ieee,
			       struct iw_request_info *info,
			       struct iw_param *data, char *extra)
{
	switch (data->flags & IW_AUTH_INDEX) {
	case IW_AUTH_WPA_VERSION:
		break;
	case IW_AUTH_CIPHER_PAIRWISE:
	case IW_AUTH_CIPHER_GROUP:
	case IW_AUTH_KEY_MGMT:
		/* Host AP driver does not use these parameters and allows
		 * wpa_supplicant to control them internally.
		 */
		break;
	case IW_AUTH_TKIP_COUNTERMEASURES:
		ieee->tkip_countermeasures = data->value;
		break;
	case IW_AUTH_DROP_UNENCRYPTED:
		ieee->drop_unencrypted = data->value;
		break;

	case IW_AUTH_80211_AUTH_ALG:
		if (data->value & IW_AUTH_ALG_SHARED_KEY) {
			ieee->open_wep = 0;
			ieee->auth_mode = 1;
		} else if (data->value & IW_AUTH_ALG_OPEN_SYSTEM) {
			ieee->open_wep = 1;
			ieee->auth_mode = 0;
		} else if (data->value & IW_AUTH_ALG_LEAP) {
			ieee->open_wep = 1;
			ieee->auth_mode = 2;
		} else
			return -EINVAL;
		break;

	case IW_AUTH_WPA_ENABLED:
		ieee->wpa_enabled = (data->value) ? 1 : 0;
		break;

	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
		ieee->ieee802_1x = data->value;
		break;
	case IW_AUTH_PRIVACY_INVOKED:
		ieee->privacy_invoked = data->value;
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}