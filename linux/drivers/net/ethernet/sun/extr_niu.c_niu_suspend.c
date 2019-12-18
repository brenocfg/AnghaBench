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
struct niu {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  reset_task; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct niu* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  niu_enable_interrupts (struct niu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_netif_stop (struct niu*) ; 
 int /*<<< orphan*/  niu_stop_hw (struct niu*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int niu_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct niu *np = netdev_priv(dev);
	unsigned long flags;

	if (!netif_running(dev))
		return 0;

	flush_work(&np->reset_task);
	niu_netif_stop(np);

	del_timer_sync(&np->timer);

	spin_lock_irqsave(&np->lock, flags);
	niu_enable_interrupts(np, 0);
	spin_unlock_irqrestore(&np->lock, flags);

	netif_device_detach(dev);

	spin_lock_irqsave(&np->lock, flags);
	niu_stop_hw(np);
	spin_unlock_irqrestore(&np->lock, flags);

	pci_save_state(pdev);

	return 0;
}