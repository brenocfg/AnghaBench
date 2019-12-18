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
 int EOPNOTSUPP ; 
#define  IW_AUTH_80211_AUTH_ALG 130 
 int IW_AUTH_ALG_OPEN_SYSTEM ; 
 int IW_AUTH_ALG_SHARED_KEY ; 
#define  IW_AUTH_DROP_UNENCRYPTED 129 
 int IW_AUTH_INDEX ; 
#define  IW_AUTH_WPA_ENABLED 128 
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_get_auth(struct net_device *dev,
			       struct iw_request_info *info,
			       union iwreq_data *wrqu, char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);
	struct iw_param *param = &wrqu->param;

	switch (param->flags & IW_AUTH_INDEX) {
	case IW_AUTH_DROP_UNENCRYPTED:
		param->value = priv->exclude_unencrypted;
		break;

	case IW_AUTH_80211_AUTH_ALG:
		if (priv->exclude_unencrypted == 1)
			param->value = IW_AUTH_ALG_SHARED_KEY;
		else
			param->value = IW_AUTH_ALG_OPEN_SYSTEM;
		break;

	case IW_AUTH_WPA_ENABLED:
		param->value = 0;
		break;

	default:
		return -EOPNOTSUPP;
	}
	return 0;
}