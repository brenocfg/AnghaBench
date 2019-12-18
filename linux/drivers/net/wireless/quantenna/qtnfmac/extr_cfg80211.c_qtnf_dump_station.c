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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct station_info {int /*<<< orphan*/  generation; scalar_t__ filled; } ;
struct TYPE_2__ {int iftype; int /*<<< orphan*/  current_bss; } ;
struct qtnf_vif {int /*<<< orphan*/  generation; int /*<<< orphan*/  netdev; TYPE_1__ wdev; int /*<<< orphan*/  sta_list; int /*<<< orphan*/  bssid; } ;
struct qtnf_sta_node {int /*<<< orphan*/  mac_addr; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  cfg80211_del_sta (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qtnf_cmd_get_sta_info (struct qtnf_vif*,int /*<<< orphan*/ *,struct station_info*) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 
 struct qtnf_sta_node* qtnf_sta_list_lookup_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int
qtnf_dump_station(struct wiphy *wiphy, struct net_device *dev,
		  int idx, u8 *mac, struct station_info *sinfo)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(dev);
	const struct qtnf_sta_node *sta_node;
	int ret;

	switch (vif->wdev.iftype) {
	case NL80211_IFTYPE_STATION:
		if (idx != 0 || !vif->wdev.current_bss)
			return -ENOENT;

		ether_addr_copy(mac, vif->bssid);
		break;
	case NL80211_IFTYPE_AP:
		sta_node = qtnf_sta_list_lookup_index(&vif->sta_list, idx);
		if (unlikely(!sta_node))
			return -ENOENT;

		ether_addr_copy(mac, sta_node->mac_addr);
		break;
	default:
		return -ENOTSUPP;
	}

	ret = qtnf_cmd_get_sta_info(vif, mac, sinfo);

	if (vif->wdev.iftype == NL80211_IFTYPE_AP) {
		if (ret == -ENOENT) {
			cfg80211_del_sta(vif->netdev, mac, GFP_KERNEL);
			sinfo->filled = 0;
		}
	}

	sinfo->generation = vif->generation;

	return ret;
}