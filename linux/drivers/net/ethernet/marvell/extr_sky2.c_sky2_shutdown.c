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
struct sky2_hw {int ports; struct net_device** dev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct sky2_hw* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  sky2_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sky2_shutdown(struct pci_dev *pdev)
{
	struct sky2_hw *hw = pci_get_drvdata(pdev);
	int port;

	for (port = 0; port < hw->ports; port++) {
		struct net_device *ndev = hw->dev[port];

		rtnl_lock();
		if (netif_running(ndev)) {
			dev_close(ndev);
			netif_device_detach(ndev);
		}
		rtnl_unlock();
	}
	sky2_suspend(&pdev->dev);
	pci_wake_from_d3(pdev, device_may_wakeup(&pdev->dev));
	pci_set_power_state(pdev, PCI_D3hot);
}