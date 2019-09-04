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
struct netdev_private {int /*<<< orphan*/  timer; struct pci_dev* pdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_list (struct net_device*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  rio_hw_stop (struct net_device*) ; 

__attribute__((used)) static int
rio_close (struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	struct pci_dev *pdev = np->pdev;

	netif_stop_queue (dev);

	rio_hw_stop(dev);

	free_irq(pdev->irq, dev);
	del_timer_sync (&np->timer);

	free_list(dev);

	return 0;
}