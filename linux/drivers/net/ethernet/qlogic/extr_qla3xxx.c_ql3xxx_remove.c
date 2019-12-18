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
struct ql3_adapter {int /*<<< orphan*/  mem_map_registers; int /*<<< orphan*/ * workqueue; int /*<<< orphan*/  tx_timeout_work; int /*<<< orphan*/  reset_work; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct ql3_adapter* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  ql_disable_interrupts (struct ql3_adapter*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void ql3xxx_remove(struct pci_dev *pdev)
{
	struct net_device *ndev = pci_get_drvdata(pdev);
	struct ql3_adapter *qdev = netdev_priv(ndev);

	unregister_netdev(ndev);

	ql_disable_interrupts(qdev);

	if (qdev->workqueue) {
		cancel_delayed_work(&qdev->reset_work);
		cancel_delayed_work(&qdev->tx_timeout_work);
		destroy_workqueue(qdev->workqueue);
		qdev->workqueue = NULL;
	}

	iounmap(qdev->mem_map_registers);
	pci_release_regions(pdev);
	free_netdev(ndev);
}