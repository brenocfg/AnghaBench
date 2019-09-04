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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ hw_addr; int /*<<< orphan*/  perm_mac_addr; int /*<<< orphan*/  mac_addr; } ;
struct atl1_adapter {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ REG_PHY_ENABLE ; 
 int /*<<< orphan*/  atl1_set_mac_addr (TYPE_1__*) ; 
 int /*<<< orphan*/  ether_addr_equal_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atl1_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void atl1_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct atl1_adapter *adapter;
	/* Device not available. Return. */
	if (!netdev)
		return;

	adapter = netdev_priv(netdev);

	/*
	 * Some atl1 boards lack persistent storage for their MAC, and get it
	 * from the BIOS during POST.  If we've been messing with the MAC
	 * address, we need to save the permanent one.
	 */
	if (!ether_addr_equal_unaligned(adapter->hw.mac_addr,
					adapter->hw.perm_mac_addr)) {
		memcpy(adapter->hw.mac_addr, adapter->hw.perm_mac_addr,
			ETH_ALEN);
		atl1_set_mac_addr(&adapter->hw);
	}

	iowrite16(0, adapter->hw.hw_addr + REG_PHY_ENABLE);
	unregister_netdev(netdev);
	pci_iounmap(pdev, adapter->hw.hw_addr);
	pci_release_regions(pdev);
	free_netdev(netdev);
	pci_disable_device(pdev);
}