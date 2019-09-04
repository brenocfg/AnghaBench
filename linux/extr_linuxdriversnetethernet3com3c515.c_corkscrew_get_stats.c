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
struct net_device {struct net_device_stats stats; int /*<<< orphan*/  base_addr; } ;
struct corkscrew_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct corkscrew_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *corkscrew_get_stats(struct net_device *dev)
{
	struct corkscrew_private *vp = netdev_priv(dev);
	unsigned long flags;

	if (netif_running(dev)) {
		spin_lock_irqsave(&vp->lock, flags);
		update_stats(dev->base_addr, dev);
		spin_unlock_irqrestore(&vp->lock, flags);
	}
	return &dev->stats;
}