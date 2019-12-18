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
struct iw_point {int flags; scalar_t__ length; int /*<<< orphan*/  pointer; } ;
union iwreq_data {struct iw_point encoding; } ;
struct wep_key {scalar_t__ len; int /*<<< orphan*/ * key; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int wep_index; int privacy_invoked; scalar_t__ authenticate_type; TYPE_1__* wep_key; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; int need_commit; TYPE_2__ reg; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 scalar_t__ AUTH_TYPE_OPEN_SYSTEM ; 
 scalar_t__ AUTH_TYPE_SHARED_KEY ; 
 int EFAULT ; 
 int EINVAL ; 
 int EPERM ; 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_INDEX ; 
 int IW_ENCODE_MODE ; 
 int IW_ENCODE_NOKEY ; 
 int IW_ENCODE_OPEN ; 
 int IW_ENCODE_RESTRICTED ; 
 scalar_t__ MAX_KEY_SIZE ; 
 scalar_t__ MIN_KEY_SIZE ; 
 scalar_t__ SLP_SLEEP ; 
 int SME_MODE_SET ; 
 int SME_WEP_FLAG ; 
 int SME_WEP_INDEX ; 
 int SME_WEP_VAL1 ; 
 int /*<<< orphan*/  WEP_OFF ; 
 int /*<<< orphan*/  WEP_ON_128BIT ; 
 int /*<<< orphan*/  WEP_ON_64BIT ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ks_wlan_setup_parameter (struct ks_wlan_private*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wep_on_off ; 

__attribute__((used)) static int ks_wlan_set_encode(struct net_device *dev,
			      struct iw_request_info *info,
			      union iwreq_data *dwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	struct iw_point *enc = &dwrq->encoding;
	struct wep_key key;
	int index = (enc->flags & IW_ENCODE_INDEX);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	if (enc->length > MAX_KEY_SIZE)
		return -EINVAL;

	/* for SLEEP MODE */
	if ((index < 0) || (index > 4))
		return -EINVAL;

	index = (index == 0) ? priv->reg.wep_index : (index - 1);

	/* Is WEP supported ? */
	/* Basic checking: do we have a key to set ? */
	if (enc->length > 0) {
		key.len = (enc->length > MIN_KEY_SIZE) ?
			   MAX_KEY_SIZE : MIN_KEY_SIZE;
		priv->reg.privacy_invoked = 0x01;
		priv->need_commit |= SME_WEP_FLAG;
		wep_on_off = (enc->length > MIN_KEY_SIZE) ?
			      WEP_ON_128BIT : WEP_ON_64BIT;
		/* Check if the key is not marked as invalid */
		if (enc->flags & IW_ENCODE_NOKEY)
			return 0;

		/* Cleanup */
		memset(key.key, 0, MAX_KEY_SIZE);
		/* Copy the key in the driver */
		if (copy_from_user(key.key, enc->pointer, enc->length)) {
			key.len = 0;
			return -EFAULT;
		}
		/* Send the key to the card */
		priv->reg.wep_key[index].size = key.len;
		memcpy(&priv->reg.wep_key[index].val[0], &key.key[0],
		       priv->reg.wep_key[index].size);
		priv->need_commit |= (SME_WEP_VAL1 << index);
		priv->reg.wep_index = index;
		priv->need_commit |= SME_WEP_INDEX;
	} else {
		if (enc->flags & IW_ENCODE_DISABLED) {
			priv->reg.wep_key[0].size = 0;
			priv->reg.wep_key[1].size = 0;
			priv->reg.wep_key[2].size = 0;
			priv->reg.wep_key[3].size = 0;
			priv->reg.privacy_invoked = 0x00;
			if (priv->reg.authenticate_type == AUTH_TYPE_SHARED_KEY)
				priv->need_commit |= SME_MODE_SET;

			priv->reg.authenticate_type = AUTH_TYPE_OPEN_SYSTEM;
			wep_on_off = WEP_OFF;
			priv->need_commit |= SME_WEP_FLAG;
		} else {
			/* set_wep_key(priv, index, 0, 0, 1);   xxx */
			if (priv->reg.wep_key[index].size == 0)
				return -EINVAL;
			priv->reg.wep_index = index;
			priv->need_commit |= SME_WEP_INDEX;
		}
	}

	/* Commit the changes if needed */
	if (enc->flags & IW_ENCODE_MODE)
		priv->need_commit |= SME_WEP_FLAG;

	if (enc->flags & IW_ENCODE_OPEN) {
		if (priv->reg.authenticate_type == AUTH_TYPE_SHARED_KEY)
			priv->need_commit |= SME_MODE_SET;

		priv->reg.authenticate_type = AUTH_TYPE_OPEN_SYSTEM;
	} else if (enc->flags & IW_ENCODE_RESTRICTED) {
		if (priv->reg.authenticate_type == AUTH_TYPE_OPEN_SYSTEM)
			priv->need_commit |= SME_MODE_SET;

		priv->reg.authenticate_type = AUTH_TYPE_SHARED_KEY;
	}
	if (priv->need_commit) {
		ks_wlan_setup_parameter(priv, priv->need_commit);
		priv->need_commit = 0;
	}
	return 0;
}