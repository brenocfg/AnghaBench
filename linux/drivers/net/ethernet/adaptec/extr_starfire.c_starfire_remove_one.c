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
struct netdev_private {int /*<<< orphan*/  base; int /*<<< orphan*/  queue_mem_dma; scalar_t__ queue_mem; int /*<<< orphan*/  queue_mem_size; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void starfire_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct netdev_private *np = netdev_priv(dev);

	BUG_ON(!dev);

	unregister_netdev(dev);

	if (np->queue_mem)
		pci_free_consistent(pdev, np->queue_mem_size, np->queue_mem, np->queue_mem_dma);


	/* XXX: add wakeup code -- requires firmware for MagicPacket */
	pci_set_power_state(pdev, PCI_D3hot);	/* go to sleep in D3 mode */
	pci_disable_device(pdev);

	iounmap(np->base);
	pci_release_regions(pdev);

	free_netdev(dev);			/* Will also free np!! */
}