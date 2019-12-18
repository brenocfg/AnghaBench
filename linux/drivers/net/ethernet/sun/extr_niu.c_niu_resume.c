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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct niu {int /*<<< orphan*/  lock; TYPE_1__ timer; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 struct niu* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int niu_init_hw (struct niu*) ; 
 int /*<<< orphan*/  niu_netif_start (struct niu*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int niu_resume(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct niu *np = netdev_priv(dev);
	unsigned long flags;
	int err;

	if (!netif_running(dev))
		return 0;

	pci_restore_state(pdev);

	netif_device_attach(dev);

	spin_lock_irqsave(&np->lock, flags);

	err = niu_init_hw(np);
	if (!err) {
		np->timer.expires = jiffies + HZ;
		add_timer(&np->timer);
		niu_netif_start(np);
	}

	spin_unlock_irqrestore(&np->lock, flags);

	return err;
}