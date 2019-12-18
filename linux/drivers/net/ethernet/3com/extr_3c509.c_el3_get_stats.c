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
struct net_device_stats {int dummy; } ;
struct net_device {struct net_device_stats stats; } ;
struct el3_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_stats (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *
el3_get_stats(struct net_device *dev)
{
	struct el3_private *lp = netdev_priv(dev);
	unsigned long flags;

	/*
	 *	This is fast enough not to bother with disable IRQ
	 *	stuff.
	 */

	spin_lock_irqsave(&lp->lock, flags);
	update_stats(dev);
	spin_unlock_irqrestore(&lp->lock, flags);
	return &dev->stats;
}