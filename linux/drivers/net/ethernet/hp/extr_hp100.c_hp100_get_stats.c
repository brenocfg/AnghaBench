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
struct net_device {int base_addr; struct net_device_stats stats; } ;
struct hp100_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  hp100_ints_off () ; 
 int /*<<< orphan*/  hp100_ints_on () ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_update_stats (struct net_device*) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct net_device_stats *hp100_get_stats(struct net_device *dev)
{
	unsigned long flags;
	int ioaddr = dev->base_addr;
	struct hp100_private *lp = netdev_priv(dev);

#ifdef HP100_DEBUG_B
	hp100_outw(0x4215, TRACE);
#endif

	spin_lock_irqsave(&lp->lock, flags);
	hp100_ints_off();	/* Useful ? Jean II */
	hp100_update_stats(dev);
	hp100_ints_on();
	spin_unlock_irqrestore(&lp->lock, flags);
	return &(dev->stats);
}