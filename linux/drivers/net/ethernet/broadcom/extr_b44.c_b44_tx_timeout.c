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
struct net_device {int dummy; } ;
struct b44 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_FULL_RESET ; 
 int /*<<< orphan*/  b44_enable_ints (struct b44*) ; 
 int /*<<< orphan*/  b44_halt (struct b44*) ; 
 int /*<<< orphan*/  b44_init_hw (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_init_rings (struct b44*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b44_tx_timeout(struct net_device *dev)
{
	struct b44 *bp = netdev_priv(dev);

	netdev_err(dev, "transmit timed out, resetting\n");

	spin_lock_irq(&bp->lock);

	b44_halt(bp);
	b44_init_rings(bp);
	b44_init_hw(bp, B44_FULL_RESET);

	spin_unlock_irq(&bp->lock);

	b44_enable_ints(bp);

	netif_wake_queue(dev);
}