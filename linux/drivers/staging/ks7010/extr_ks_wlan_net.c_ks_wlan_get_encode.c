#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iw_point {int flags; int length; } ;
union iwreq_data {struct iw_point encoding; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int authenticate_type; int wep_index; TYPE_1__* wep_key; scalar_t__ privacy_invoked; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_2__ reg; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  val; } ;

/* Variables and functions */
#define  AUTH_TYPE_OPEN_SYSTEM 129 
#define  AUTH_TYPE_SHARED_KEY 128 
 int EPERM ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_OPEN ; 
 int IW_ENCODE_RESTRICTED ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_get_encode(struct net_device *dev,
			      struct iw_request_info *info,
			      union iwreq_data *dwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	struct iw_point *enc = &dwrq->encoding;
	int index = (enc->flags & IW_ENCODE_INDEX) - 1;

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	enc->flags = IW_ENCODE_DISABLED;

	/* Check encryption mode */
	switch (priv->reg.authenticate_type) {
	case AUTH_TYPE_OPEN_SYSTEM:
		enc->flags = IW_ENCODE_OPEN;
		break;
	case AUTH_TYPE_SHARED_KEY:
		enc->flags = IW_ENCODE_RESTRICTED;
		break;
	}

	/* Which key do we want ? -1 -> tx index */
	if ((index < 0) || (index >= 4))
		index = priv->reg.wep_index;
	if (priv->reg.privacy_invoked) {
		enc->flags &= ~IW_ENCODE_DISABLED;
		/* dwrq->flags |= IW_ENCODE_NOKEY; */
	}
	enc->flags |= index + 1;
	/* Copy the key to the user buffer */
	if (index >= 0 && index < 4) {
		enc->length = (priv->reg.wep_key[index].size <= 16) ?
				priv->reg.wep_key[index].size : 0;
		memcpy(extra, priv->reg.wep_key[index].val, enc->length);
	}

	return 0;
}