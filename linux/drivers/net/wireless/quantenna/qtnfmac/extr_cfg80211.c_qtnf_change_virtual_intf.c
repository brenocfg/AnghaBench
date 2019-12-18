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
struct wiphy {int dummy; } ;
struct vif_params {int use_4addr; int /*<<< orphan*/ * macaddr; } ;
struct TYPE_3__ {int iftype; } ;
struct qtnf_vif {TYPE_1__ wdev; int /*<<< orphan*/  vifid; TYPE_2__* mac; } ;
struct net_device {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_4__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send_change_intf_type (struct qtnf_vif*,int,int,int /*<<< orphan*/ *) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  qtnf_scan_done (TYPE_2__*,int) ; 
 int qtnf_validate_iface_combinations (struct wiphy*,struct qtnf_vif*,int) ; 

__attribute__((used)) static int
qtnf_change_virtual_intf(struct wiphy *wiphy,
			 struct net_device *dev,
			 enum nl80211_iftype type,
			 struct vif_params *params)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(dev);
	u8 *mac_addr = NULL;
	int use4addr = 0;
	int ret;

	ret = qtnf_validate_iface_combinations(wiphy, vif, type);
	if (ret) {
		pr_err("VIF%u.%u combination check: failed to set type %d\n",
		       vif->mac->macid, vif->vifid, type);
		return ret;
	}

	if (params) {
		mac_addr = params->macaddr;
		use4addr = params->use_4addr;
	}

	qtnf_scan_done(vif->mac, true);

	ret = qtnf_cmd_send_change_intf_type(vif, type, use4addr, mac_addr);
	if (ret) {
		pr_err("VIF%u.%u: failed to change type to %d\n",
		       vif->mac->macid, vif->vifid, type);
		return ret;
	}

	vif->wdev.iftype = type;
	return 0;
}