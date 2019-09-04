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
struct netdev_private {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __set_rx_mode (struct net_device*) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void set_rx_mode(struct net_device *dev)
{
	spinlock_t *lp = &((struct netdev_private *)netdev_priv(dev))->lock;
	unsigned long flags;
	spin_lock_irqsave(lp, flags);
	__set_rx_mode(dev);
	spin_unlock_irqrestore(lp, flags);
}