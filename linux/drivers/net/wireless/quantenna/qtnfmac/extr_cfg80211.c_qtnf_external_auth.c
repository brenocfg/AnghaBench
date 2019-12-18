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
struct TYPE_3__ {scalar_t__ iftype; } ;
struct qtnf_vif {int /*<<< orphan*/  vifid; TYPE_2__* mac; int /*<<< orphan*/  bssid; TYPE_1__ wdev; } ;
struct net_device {int dummy; } ;
struct cfg80211_external_auth_params {int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int qtnf_cmd_send_external_auth (struct qtnf_vif*,struct cfg80211_external_auth_params*) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 

__attribute__((used)) static int
qtnf_external_auth(struct wiphy *wiphy, struct net_device *dev,
		   struct cfg80211_external_auth_params *auth)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(dev);
	int ret;

	if (vif->wdev.iftype != NL80211_IFTYPE_STATION)
		return -EOPNOTSUPP;

	if (!ether_addr_equal(vif->bssid, auth->bssid))
		pr_warn("unexpected bssid: %pM", auth->bssid);

	ret = qtnf_cmd_send_external_auth(vif, auth);
	if (ret) {
		pr_err("VIF%u.%u: failed to report external auth\n",
		       vif->mac->macid, vif->vifid);
		goto out;
	}

out:
	return ret;
}