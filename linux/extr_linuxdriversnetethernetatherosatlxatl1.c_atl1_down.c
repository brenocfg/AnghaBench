#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* cmb; } ;
struct atl1_adapter {int phy_timer_pending; int link_duplex; int /*<<< orphan*/  link_speed; TYPE_2__ cmb; int /*<<< orphan*/  hw; TYPE_3__* pdev; int /*<<< orphan*/  phy_config_timer; int /*<<< orphan*/  napi; struct net_device* netdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {scalar_t__ int_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPEED_0 ; 
 int /*<<< orphan*/  atl1_clean_rx_ring (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_clean_tx_ring (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_reset_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atlx_irq_disable (struct atl1_adapter*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_3__*) ; 

__attribute__((used)) static void atl1_down(struct atl1_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	napi_disable(&adapter->napi);
	netif_stop_queue(netdev);
	del_timer_sync(&adapter->phy_config_timer);
	adapter->phy_timer_pending = false;

	atlx_irq_disable(adapter);
	free_irq(adapter->pdev->irq, netdev);
	pci_disable_msi(adapter->pdev);
	atl1_reset_hw(&adapter->hw);
	adapter->cmb.cmb->int_stats = 0;

	adapter->link_speed = SPEED_0;
	adapter->link_duplex = -1;
	netif_carrier_off(netdev);

	atl1_clean_tx_ring(adapter);
	atl1_clean_rx_ring(adapter);
}