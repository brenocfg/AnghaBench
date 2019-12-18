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
struct qtnf_wmac {int dummy; } ;
struct TYPE_2__ {scalar_t__ iftype; int /*<<< orphan*/  wiphy; } ;
struct qtnf_vif {TYPE_1__ wdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  qtnf_disconnect (int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  qtnf_scan_done (struct qtnf_wmac*,int) ; 
 struct qtnf_wmac* wiphy_priv (int /*<<< orphan*/ ) ; 

void qtnf_virtual_intf_cleanup(struct net_device *ndev)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(ndev);
	struct qtnf_wmac *mac = wiphy_priv(vif->wdev.wiphy);

	if (vif->wdev.iftype == NL80211_IFTYPE_STATION)
		qtnf_disconnect(vif->wdev.wiphy, ndev,
				WLAN_REASON_DEAUTH_LEAVING);

	qtnf_scan_done(mac, true);
}