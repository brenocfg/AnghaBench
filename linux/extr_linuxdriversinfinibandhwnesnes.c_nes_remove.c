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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct net_device {int dummy; } ;
struct nes_device {int /*<<< orphan*/  regs; scalar_t__ msi_enabled; TYPE_1__* nesadapter; int /*<<< orphan*/  work; scalar_t__ link_recheck; int /*<<< orphan*/  dpc_tasklet; int /*<<< orphan*/  list; scalar_t__ netdev_count; struct net_device** netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  netdev_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct nes_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nes_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nes_destroy_adapter (TYPE_1__*) ; 
 int /*<<< orphan*/  nes_destroy_cqp (struct nes_device*) ; 
 int /*<<< orphan*/  nes_inetaddr_notifier ; 
 int /*<<< orphan*/  nes_net_notifier ; 
 int /*<<< orphan*/  nes_netdev_destroy (struct net_device*) ; 
 scalar_t__ nes_notifiers_registered ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct nes_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_inetaddr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netevent_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nes_remove(struct pci_dev *pcidev)
{
	struct nes_device *nesdev = pci_get_drvdata(pcidev);
	struct net_device *netdev;
	int netdev_index = 0;
	unsigned long flags;

	if (nesdev->netdev_count) {
		netdev = nesdev->netdev[netdev_index];
		if (netdev) {
			netif_stop_queue(netdev);
			unregister_netdev(netdev);
			nes_netdev_destroy(netdev);

			nesdev->netdev[netdev_index] = NULL;
			nesdev->netdev_count--;
			nesdev->nesadapter->netdev_count--;
		}
	}

	nes_notifiers_registered--;
	if (nes_notifiers_registered == 0) {
		unregister_netevent_notifier(&nes_net_notifier);
		unregister_inetaddr_notifier(&nes_inetaddr_notifier);
	}

	list_del(&nesdev->list);
	nes_destroy_cqp(nesdev);

	free_irq(pcidev->irq, nesdev);
	tasklet_kill(&nesdev->dpc_tasklet);

	spin_lock_irqsave(&nesdev->nesadapter->phy_lock, flags);
	if (nesdev->link_recheck) {
		spin_unlock_irqrestore(&nesdev->nesadapter->phy_lock, flags);
		cancel_delayed_work_sync(&nesdev->work);
	} else {
		spin_unlock_irqrestore(&nesdev->nesadapter->phy_lock, flags);
	}

	/* Deallocate the Adapter Structure */
	nes_destroy_adapter(nesdev->nesadapter);

	if (nesdev->msi_enabled) {
		pci_disable_msi(pcidev);
	}

	iounmap(nesdev->regs);
	kfree(nesdev);

	/* nes_debug(NES_DBG_SHUTDOWN, "calling pci_release_regions.\n"); */
	pci_release_regions(pcidev);
	pci_disable_device(pcidev);
	pci_set_drvdata(pcidev, NULL);
}