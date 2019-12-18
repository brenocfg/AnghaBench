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
struct qtnf_vif {int /*<<< orphan*/  vifid; TYPE_1__* mac; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qtnf_cmd_send_updown_intf (struct qtnf_vif*,int) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 

void qtnf_netdev_updown(struct net_device *ndev, bool up)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(ndev);

	if (qtnf_cmd_send_updown_intf(vif, up))
		pr_err("failed to send %s command to VIF%u.%u\n",
		       up ? "UP" : "DOWN", vif->mac->macid, vif->vifid);
}