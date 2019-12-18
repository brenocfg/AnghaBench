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
struct wiphy {int dummy; } ;
struct station_del_parameters {int /*<<< orphan*/  mac; } ;
struct TYPE_4__ {scalar_t__ iftype; } ;
struct qtnf_vif {int /*<<< orphan*/  vifid; TYPE_1__* mac; int /*<<< orphan*/  sta_list; TYPE_2__ wdev; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qtnf_cmd_send_del_sta (struct qtnf_vif*,struct station_del_parameters*) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  qtnf_sta_list_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qtnf_del_station(struct wiphy *wiphy, struct net_device *dev,
		 struct station_del_parameters *params)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(dev);
	int ret;

	if (params->mac &&
	    (vif->wdev.iftype == NL80211_IFTYPE_AP) &&
	    !is_broadcast_ether_addr(params->mac) &&
	    !qtnf_sta_list_lookup(&vif->sta_list, params->mac))
		return 0;

	ret = qtnf_cmd_send_del_sta(vif, params);
	if (ret)
		pr_err("VIF%u.%u: failed to delete STA %pM\n",
		       vif->mac->macid, vif->vifid, params->mac);

	return ret;
}