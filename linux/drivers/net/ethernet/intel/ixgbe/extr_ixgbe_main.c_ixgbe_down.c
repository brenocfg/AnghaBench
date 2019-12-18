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
struct TYPE_5__ {int /*<<< orphan*/  (* disable_tx_laser ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct ixgbe_hw {TYPE_3__ mac; } ;
struct ixgbe_adapter {int num_vfs; int /*<<< orphan*/  pdev; TYPE_1__* vfinfo; struct ixgbe_hw hw; int /*<<< orphan*/  service_timer; int /*<<< orphan*/  flags; int /*<<< orphan*/  flags2; int /*<<< orphan*/  state; scalar_t__* xdp_ring; struct net_device* netdev; } ;
struct TYPE_4__ {int clear_to_send; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_EITRSEL ; 
 int /*<<< orphan*/  IXGBE_FLAG2_FDIR_REQUIRES_REINIT ; 
 int /*<<< orphan*/  IXGBE_FLAG_NEED_LINK_UPDATE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  __IXGBE_RESET_REQUESTED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_clean_all_rx_rings (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_clean_all_tx_rings (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_disable_rx (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_disable_tx (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_disable_tx_rx (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_irq_disable (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_napi_disable_all (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ping_all_vfs (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_reset (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ixgbe_down(struct ixgbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct ixgbe_hw *hw = &adapter->hw;
	int i;

	/* signal that we are down to the interrupt handler */
	if (test_and_set_bit(__IXGBE_DOWN, &adapter->state))
		return; /* do nothing if already down */

	/* Shut off incoming Tx traffic */
	netif_tx_stop_all_queues(netdev);

	/* call carrier off first to avoid false dev_watchdog timeouts */
	netif_carrier_off(netdev);
	netif_tx_disable(netdev);

	/* Disable Rx */
	ixgbe_disable_rx(adapter);

	/* synchronize_rcu() needed for pending XDP buffers to drain */
	if (adapter->xdp_ring[0])
		synchronize_rcu();

	ixgbe_irq_disable(adapter);

	ixgbe_napi_disable_all(adapter);

	clear_bit(__IXGBE_RESET_REQUESTED, &adapter->state);
	adapter->flags2 &= ~IXGBE_FLAG2_FDIR_REQUIRES_REINIT;
	adapter->flags &= ~IXGBE_FLAG_NEED_LINK_UPDATE;

	del_timer_sync(&adapter->service_timer);

	if (adapter->num_vfs) {
		/* Clear EITR Select mapping */
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EITRSEL, 0);

		/* Mark all the VFs as inactive */
		for (i = 0 ; i < adapter->num_vfs; i++)
			adapter->vfinfo[i].clear_to_send = false;

		/* ping all the active vfs to let them know we are going down */
		ixgbe_ping_all_vfs(adapter);

		/* Disable all VFTE/VFRE TX/RX */
		ixgbe_disable_tx_rx(adapter);
	}

	/* disable transmits in the hardware now that interrupts are off */
	ixgbe_disable_tx(adapter);

	if (!pci_channel_offline(adapter->pdev))
		ixgbe_reset(adapter);

	/* power down the optics for 82599 SFP+ fiber */
	if (hw->mac.ops.disable_tx_laser)
		hw->mac.ops.disable_tx_laser(hw);

	ixgbe_clean_all_tx_rings(adapter);
	ixgbe_clean_all_rx_rings(adapter);
}