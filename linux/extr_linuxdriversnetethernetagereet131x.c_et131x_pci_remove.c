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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct et131x_adapter {int /*<<< orphan*/  regs; int /*<<< orphan*/  mii_bus; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  et131x_adapter_memory_free (struct et131x_adapter*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void et131x_pci_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct et131x_adapter *adapter = netdev_priv(netdev);

	unregister_netdev(netdev);
	netif_napi_del(&adapter->napi);
	phy_disconnect(netdev->phydev);
	mdiobus_unregister(adapter->mii_bus);
	mdiobus_free(adapter->mii_bus);

	et131x_adapter_memory_free(adapter);
	iounmap(adapter->regs);
	pci_dev_put(pdev);

	free_netdev(netdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
}