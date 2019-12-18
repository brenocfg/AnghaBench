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
struct net_device {int dummy; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {int num_rx_queues; int num_tx_queues; int num_xdp_queues; int /*<<< orphan*/  pdev; TYPE_2__** xdp_ring; TYPE_1__** tx_ring; int /*<<< orphan*/  service_timer; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  state; struct ixgbe_hw hw; struct net_device* netdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg_idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_TXDCTL_SWFLSH ; 
 int /*<<< orphan*/  IXGBE_VFTXDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbevf_clean_all_rx_rings (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_clean_all_tx_rings (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_disable_rx_queue (struct ixgbevf_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_irq_disable (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_napi_disable_all (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_reset (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void ixgbevf_down(struct ixgbevf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct ixgbe_hw *hw = &adapter->hw;
	int i;

	/* signal that we are down to the interrupt handler */
	if (test_and_set_bit(__IXGBEVF_DOWN, &adapter->state))
		return; /* do nothing if already down */

	/* disable all enabled Rx queues */
	for (i = 0; i < adapter->num_rx_queues; i++)
		ixgbevf_disable_rx_queue(adapter, adapter->rx_ring[i]);

	usleep_range(10000, 20000);

	netif_tx_stop_all_queues(netdev);

	/* call carrier off first to avoid false dev_watchdog timeouts */
	netif_carrier_off(netdev);
	netif_tx_disable(netdev);

	ixgbevf_irq_disable(adapter);

	ixgbevf_napi_disable_all(adapter);

	del_timer_sync(&adapter->service_timer);

	/* disable transmits in the hardware now that interrupts are off */
	for (i = 0; i < adapter->num_tx_queues; i++) {
		u8 reg_idx = adapter->tx_ring[i]->reg_idx;

		IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(reg_idx),
				IXGBE_TXDCTL_SWFLSH);
	}

	for (i = 0; i < adapter->num_xdp_queues; i++) {
		u8 reg_idx = adapter->xdp_ring[i]->reg_idx;

		IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(reg_idx),
				IXGBE_TXDCTL_SWFLSH);
	}

	if (!pci_channel_offline(adapter->pdev))
		ixgbevf_reset(adapter);

	ixgbevf_clean_all_tx_rings(adapter);
	ixgbevf_clean_all_rx_rings(adapter);
}