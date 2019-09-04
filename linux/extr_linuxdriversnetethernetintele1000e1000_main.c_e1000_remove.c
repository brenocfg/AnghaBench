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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct e1000_hw {scalar_t__ mac_type; scalar_t__ flash_address; scalar_t__ hw_addr; scalar_t__ ce4100_gbe_mdio_base_virt; } ;
struct e1000_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  bars; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  __E1000_DISABLED ; 
 scalar_t__ e1000_ce4100 ; 
 int /*<<< orphan*/  e1000_down_and_stop (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_phy_hw_reset (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_release_manageability (struct e1000_adapter*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_selected_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void e1000_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	bool disable_dev;

	e1000_down_and_stop(adapter);
	e1000_release_manageability(adapter);

	unregister_netdev(netdev);

	e1000_phy_hw_reset(hw);

	kfree(adapter->tx_ring);
	kfree(adapter->rx_ring);

	if (hw->mac_type == e1000_ce4100)
		iounmap(hw->ce4100_gbe_mdio_base_virt);
	iounmap(hw->hw_addr);
	if (hw->flash_address)
		iounmap(hw->flash_address);
	pci_release_selected_regions(pdev, adapter->bars);

	disable_dev = !test_and_set_bit(__E1000_DISABLED, &adapter->flags);
	free_netdev(netdev);

	if (disable_dev)
		pci_disable_device(pdev);
}