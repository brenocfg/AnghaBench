#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct e1000_rx_ring {int dummy; } ;
struct e1000_hw {int pci_cmd_word; } ;
struct e1000_adapter {int /*<<< orphan*/  (* alloc_rx_buf ) (struct e1000_adapter*,struct e1000_rx_ring*,int /*<<< orphan*/ ) ;struct e1000_rx_ring* rx_ring; struct net_device* netdev; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_DESC_UNUSED (struct e1000_rx_ring*) ; 
 int /*<<< orphan*/  E1000_RCTL_RST ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int PCI_COMMAND_INVALIDATE ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  e1000_configure_rx (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_pci_set_mwi (struct e1000_hw*) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_adapter*,struct e1000_rx_ring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_leave_82542_rst(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	u32 rctl;

	rctl = er32(RCTL);
	rctl &= ~E1000_RCTL_RST;
	ew32(RCTL, rctl);
	E1000_WRITE_FLUSH();
	mdelay(5);

	if (hw->pci_cmd_word & PCI_COMMAND_INVALIDATE)
		e1000_pci_set_mwi(hw);

	if (netif_running(netdev)) {
		/* No need to loop, because 82542 supports only 1 queue */
		struct e1000_rx_ring *ring = &adapter->rx_ring[0];
		e1000_configure_rx(adapter);
		adapter->alloc_rx_buf(adapter, ring, E1000_DESC_UNUSED(ring));
	}
}