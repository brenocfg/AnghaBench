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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct atl1_adapter {int /*<<< orphan*/  wol; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  atl1_suspend (int /*<<< orphan*/ *) ; 
 struct atl1_adapter* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl1_shutdown(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct atl1_adapter *adapter = netdev_priv(netdev);

#ifdef CONFIG_PM_SLEEP
	atl1_suspend(&pdev->dev);
#endif
	pci_wake_from_d3(pdev, adapter->wol);
	pci_set_power_state(pdev, PCI_D3hot);
}