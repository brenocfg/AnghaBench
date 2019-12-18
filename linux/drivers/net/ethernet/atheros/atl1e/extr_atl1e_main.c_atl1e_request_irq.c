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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct atl1e_adapter {struct net_device* netdev; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  atl1e_intr ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int atl1e_request_irq(struct atl1e_adapter *adapter)
{
	struct pci_dev    *pdev   = adapter->pdev;
	struct net_device *netdev = adapter->netdev;
	int err = 0;

	err = request_irq(pdev->irq, atl1e_intr, IRQF_SHARED, netdev->name,
			  netdev);
	if (err) {
		netdev_dbg(adapter->netdev,
			   "Unable to allocate interrupt Error: %d\n", err);
		return err;
	}
	netdev_dbg(netdev, "atl1e_request_irq OK\n");
	return err;
}