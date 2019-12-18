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
struct qtnf_wmac {int /*<<< orphan*/  macid; struct qtnf_bus* bus; } ;
struct qtnf_vif {scalar_t__ cons_tx_timeout_cnt; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  vifid; struct qtnf_wmac* mac; } ;
struct qtnf_bus {int /*<<< orphan*/  workqueue; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ QTNF_TX_TIMEOUT_TRSHLD ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netdev_name (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_data_tx_timeout (struct qtnf_bus*,struct net_device*) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void qtnf_netdev_tx_timeout(struct net_device *ndev)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(ndev);
	struct qtnf_wmac *mac;
	struct qtnf_bus *bus;

	if (unlikely(!vif || !vif->mac || !vif->mac->bus))
		return;

	mac = vif->mac;
	bus = mac->bus;

	pr_warn("VIF%u.%u: Tx timeout- %lu\n", mac->macid, vif->vifid, jiffies);

	qtnf_bus_data_tx_timeout(bus, ndev);
	ndev->stats.tx_errors++;

	if (++vif->cons_tx_timeout_cnt > QTNF_TX_TIMEOUT_TRSHLD) {
		pr_err("Tx timeout threshold exceeded !\n");
		pr_err("schedule interface %s reset !\n", netdev_name(ndev));
		queue_work(bus->workqueue, &vif->reset_work);
	}
}