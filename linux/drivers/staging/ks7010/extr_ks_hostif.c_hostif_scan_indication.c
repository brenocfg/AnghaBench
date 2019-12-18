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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int size; TYPE_2__* ap; } ;
struct ks_wlan_private {int scan_ind_count; int /*<<< orphan*/  net_dev; TYPE_1__ aplist; scalar_t__ rxp; } ;
struct ap_info {scalar_t__ frame_type; int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {int /*<<< orphan*/ * bssid; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_STYPE_PROBE_RESP ; 
 int LOCAL_APLIST_MAX ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ap_information (struct ks_wlan_private*,struct ap_info*,TYPE_2__*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static
void hostif_scan_indication(struct ks_wlan_private *priv)
{
	int i;
	struct ap_info *ap_info;

	netdev_dbg(priv->net_dev,
		   "scan_ind_count = %d\n", priv->scan_ind_count);
	ap_info = (struct ap_info *)(priv->rxp);

	if (priv->scan_ind_count) {
		/* bssid check */
		for (i = 0; i < priv->aplist.size; i++) {
			u8 *bssid = priv->aplist.ap[i].bssid;

			if (ether_addr_equal(ap_info->bssid, bssid))
				continue;

			if (ap_info->frame_type == IEEE80211_STYPE_PROBE_RESP)
				get_ap_information(priv, ap_info,
						   &priv->aplist.ap[i]);
			return;
		}
	}
	priv->scan_ind_count++;
	if (priv->scan_ind_count < LOCAL_APLIST_MAX + 1) {
		netdev_dbg(priv->net_dev, " scan_ind_count=%d :: aplist.size=%d\n",
			   priv->scan_ind_count, priv->aplist.size);
		get_ap_information(priv, (struct ap_info *)(priv->rxp),
				   &priv->aplist.ap[priv->scan_ind_count - 1]);
		priv->aplist.size = priv->scan_ind_count;
	} else {
		netdev_dbg(priv->net_dev, " count over :: scan_ind_count=%d\n",
			   priv->scan_ind_count);
	}
}