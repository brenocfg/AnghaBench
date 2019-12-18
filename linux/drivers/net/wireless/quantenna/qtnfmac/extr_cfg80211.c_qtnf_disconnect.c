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
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct qtnf_wmac {int /*<<< orphan*/  macid; } ;
struct TYPE_2__ {scalar_t__ iftype; scalar_t__ current_bss; } ;
struct qtnf_vif {int /*<<< orphan*/  netdev; TYPE_1__ wdev; int /*<<< orphan*/  vifid; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  cfg80211_disconnected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int qtnf_cmd_send_disconnect (struct qtnf_vif*,int /*<<< orphan*/ ) ; 
 struct qtnf_vif* qtnf_mac_get_base_vif (struct qtnf_wmac*) ; 
 struct qtnf_wmac* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int
qtnf_disconnect(struct wiphy *wiphy, struct net_device *dev,
		u16 reason_code)
{
	struct qtnf_wmac *mac = wiphy_priv(wiphy);
	struct qtnf_vif *vif;
	int ret = 0;

	vif = qtnf_mac_get_base_vif(mac);
	if (!vif) {
		pr_err("MAC%u: primary VIF is not configured\n", mac->macid);
		return -EFAULT;
	}

	if (vif->wdev.iftype != NL80211_IFTYPE_STATION) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	ret = qtnf_cmd_send_disconnect(vif, reason_code);
	if (ret)
		pr_err("VIF%u.%u: failed to disconnect\n",
		       mac->macid, vif->vifid);

	if (vif->wdev.current_bss) {
		netif_carrier_off(vif->netdev);
		cfg80211_disconnected(vif->netdev, reason_code,
				      NULL, 0, true, GFP_KERNEL);
	}

out:
	return ret;
}