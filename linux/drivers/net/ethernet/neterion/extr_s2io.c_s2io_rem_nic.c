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
struct s2io_nic {int /*<<< orphan*/  bar1; int /*<<< orphan*/  bar0; int /*<<< orphan*/  set_link_task; int /*<<< orphan*/  rst_timer_task; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_DBG ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_shared_mem (struct s2io_nic*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void s2io_rem_nic(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct s2io_nic *sp;

	if (dev == NULL) {
		DBG_PRINT(ERR_DBG, "Driver Data is NULL!!\n");
		return;
	}

	sp = netdev_priv(dev);

	cancel_work_sync(&sp->rst_timer_task);
	cancel_work_sync(&sp->set_link_task);

	unregister_netdev(dev);

	free_shared_mem(sp);
	iounmap(sp->bar0);
	iounmap(sp->bar1);
	pci_release_regions(pdev);
	free_netdev(dev);
	pci_disable_device(pdev);
}