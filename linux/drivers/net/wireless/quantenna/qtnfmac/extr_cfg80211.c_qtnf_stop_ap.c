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
struct wiphy {int dummy; } ;
struct qtnf_vif {int /*<<< orphan*/  netdev; int /*<<< orphan*/  vifid; TYPE_1__* mac; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qtnf_cmd_send_stop_ap (struct qtnf_vif*) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  qtnf_scan_done (TYPE_1__*,int) ; 

__attribute__((used)) static int qtnf_stop_ap(struct wiphy *wiphy, struct net_device *dev)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(dev);
	int ret;

	qtnf_scan_done(vif->mac, true);

	ret = qtnf_cmd_send_stop_ap(vif);
	if (ret)
		pr_err("VIF%u.%u: failed to stop AP operation in FW\n",
		       vif->mac->macid, vif->vifid);

	netif_carrier_off(vif->netdev);

	return ret;
}