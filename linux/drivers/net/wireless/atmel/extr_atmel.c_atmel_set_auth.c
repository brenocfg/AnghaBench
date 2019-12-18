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
struct iw_param {int flags; int value; } ;
union iwreq_data {struct iw_param param; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct atmel_private {int exclude_unencrypted; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  IW_AUTH_80211_AUTH_ALG 136 
 int IW_AUTH_ALG_OPEN_SYSTEM ; 
 int IW_AUTH_ALG_SHARED_KEY ; 
#define  IW_AUTH_CIPHER_GROUP 135 
#define  IW_AUTH_CIPHER_PAIRWISE 134 
#define  IW_AUTH_DROP_UNENCRYPTED 133 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_KEY_MGMT 132 
#define  IW_AUTH_PRIVACY_INVOKED 131 
#define  IW_AUTH_RX_UNENCRYPTED_EAPOL 130 
#define  IW_AUTH_WPA_ENABLED 129 
#define  IW_AUTH_WPA_VERSION 128 
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_set_auth(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);
	struct iw_param *param = &wrqu->param;

	switch (param->flags & IW_AUTH_INDEX) {
	case IW_AUTH_WPA_VERSION:
	case IW_AUTH_CIPHER_PAIRWISE:
	case IW_AUTH_CIPHER_GROUP:
	case IW_AUTH_KEY_MGMT:
	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
	case IW_AUTH_PRIVACY_INVOKED:
		/*
		 * atmel does not use these parameters
		 */
		break;

	case IW_AUTH_DROP_UNENCRYPTED:
		priv->exclude_unencrypted = param->value ? 1 : 0;
		break;

	case IW_AUTH_80211_AUTH_ALG: {
			if (param->value & IW_AUTH_ALG_SHARED_KEY) {
				priv->exclude_unencrypted = 1;
			} else if (param->value & IW_AUTH_ALG_OPEN_SYSTEM) {
				priv->exclude_unencrypted = 0;
			} else
				return -EINVAL;
			break;
		}

	case IW_AUTH_WPA_ENABLED:
		/* Silently accept disable of WPA */
		if (param->value > 0)
			return -EOPNOTSUPP;
		break;

	default:
		return -EOPNOTSUPP;
	}
	return -EINPROGRESS;
}