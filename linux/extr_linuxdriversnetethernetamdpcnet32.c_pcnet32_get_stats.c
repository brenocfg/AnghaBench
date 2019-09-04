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
struct pcnet32_private {int /*<<< orphan*/  lock; TYPE_1__* a; } ;
struct net_device_stats {int /*<<< orphan*/  rx_missed_errors; } ;
struct net_device {unsigned long base_addr; struct net_device_stats stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_csr ) (unsigned long,int) ;} ;

/* Variables and functions */
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (unsigned long,int) ; 

__attribute__((used)) static struct net_device_stats *pcnet32_get_stats(struct net_device *dev)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	unsigned long ioaddr = dev->base_addr;
	unsigned long flags;

	spin_lock_irqsave(&lp->lock, flags);
	dev->stats.rx_missed_errors = lp->a->read_csr(ioaddr, 112);
	spin_unlock_irqrestore(&lp->lock, flags);

	return &dev->stats;
}