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
struct e1000_hw {int dummy; } ;
struct e1000_adapter {struct net_device* netdev; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RCTL_RST ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  e1000_clean_all_rx_rings (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_pci_clear_mwi (struct e1000_hw*) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static void e1000_enter_82542_rst(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	u32 rctl;

	e1000_pci_clear_mwi(hw);

	rctl = er32(RCTL);
	rctl |= E1000_RCTL_RST;
	ew32(RCTL, rctl);
	E1000_WRITE_FLUSH();
	mdelay(5);

	if (netif_running(netdev))
		e1000_clean_all_rx_rings(adapter);
}