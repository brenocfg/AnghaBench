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
struct net_device {int /*<<< orphan*/  irq; scalar_t__ phydev; } ;
struct au1000_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  au1000_reset_mac_unlocked (struct net_device*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct au1000_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct au1000_private* const,int /*<<< orphan*/ ,struct net_device*,char*,struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int au1000_close(struct net_device *dev)
{
	unsigned long flags;
	struct au1000_private *const aup = netdev_priv(dev);

	netif_dbg(aup, drv, dev, "close: dev=%p\n", dev);

	if (dev->phydev)
		phy_stop(dev->phydev);

	spin_lock_irqsave(&aup->lock, flags);

	au1000_reset_mac_unlocked(dev);

	/* stop the device */
	netif_stop_queue(dev);

	/* disable the interrupt */
	free_irq(dev->irq, dev);
	spin_unlock_irqrestore(&aup->lock, flags);

	return 0;
}