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
struct qtnf_wmac {struct qtnf_vif* iflist; } ;
struct qtnf_vif {scalar_t__ netdev; TYPE_1__* mac; } ;
struct TYPE_4__ {int mac_bitmap; } ;
struct qtnf_bus {struct qtnf_wmac** mac; TYPE_2__ hw_info; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct qtnf_bus* bus; } ;

/* Variables and functions */
 int BIT (int) ; 
 int QTNF_MAX_INTF ; 
 int QTNF_MAX_MAC ; 
 scalar_t__ netif_queue_stopped (scalar_t__) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (scalar_t__) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

void qtnf_wake_all_queues(struct net_device *ndev)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(ndev);
	struct qtnf_wmac *mac;
	struct qtnf_bus *bus;
	int macid;
	int i;

	if (unlikely(!vif || !vif->mac || !vif->mac->bus))
		return;

	bus = vif->mac->bus;

	for (macid = 0; macid < QTNF_MAX_MAC; macid++) {
		if (!(bus->hw_info.mac_bitmap & BIT(macid)))
			continue;

		mac = bus->mac[macid];
		for (i = 0; i < QTNF_MAX_INTF; i++) {
			vif = &mac->iflist[i];
			if (vif->netdev && netif_queue_stopped(vif->netdev))
				netif_tx_wake_all_queues(vif->netdev);
		}
	}
}