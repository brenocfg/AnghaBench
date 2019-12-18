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
struct TYPE_2__ {scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  u8 ;
struct orinoco_private {scalar_t__ wpa_ie_len; int /*<<< orphan*/ * wpa_ie; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IEEE80211_MAX_DATA_LEN ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_set_genie(struct net_device *dev,
				   struct iw_request_info *info,
				   union iwreq_data *wrqu, char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);
	u8 *buf;
	unsigned long flags;

	/* cut off at IEEE80211_MAX_DATA_LEN */
	if ((wrqu->data.length > IEEE80211_MAX_DATA_LEN) ||
	    (wrqu->data.length && (extra == NULL)))
		return -EINVAL;

	if (wrqu->data.length) {
		buf = kmemdup(extra, wrqu->data.length, GFP_KERNEL);
		if (buf == NULL)
			return -ENOMEM;
	} else
		buf = NULL;

	if (orinoco_lock(priv, &flags) != 0) {
		kfree(buf);
		return -EBUSY;
	}

	kfree(priv->wpa_ie);
	priv->wpa_ie = buf;
	priv->wpa_ie_len = wrqu->data.length;

	if (priv->wpa_ie) {
		/* Looks like wl_lkm wants to check the auth alg, and
		 * somehow pass it to the firmware.
		 * Instead it just calls the key mgmt rid
		 *   - we do this in set auth.
		 */
	}

	orinoco_unlock(priv, &flags);
	return 0;
}