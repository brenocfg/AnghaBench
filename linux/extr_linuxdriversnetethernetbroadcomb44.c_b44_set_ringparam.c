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
struct ethtool_ringparam {int rx_pending; scalar_t__ rx_mini_pending; scalar_t__ rx_jumbo_pending; int tx_pending; } ;
struct b44 {int rx_pending; int tx_pending; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_FULL_RESET ; 
 int B44_RX_RING_SIZE ; 
 int B44_TX_RING_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  b44_enable_ints (struct b44*) ; 
 int /*<<< orphan*/  b44_halt (struct b44*) ; 
 int /*<<< orphan*/  b44_init_hw (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_init_rings (struct b44*) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b44_set_ringparam(struct net_device *dev,
			     struct ethtool_ringparam *ering)
{
	struct b44 *bp = netdev_priv(dev);

	if ((ering->rx_pending > B44_RX_RING_SIZE - 1) ||
	    (ering->rx_mini_pending != 0) ||
	    (ering->rx_jumbo_pending != 0) ||
	    (ering->tx_pending > B44_TX_RING_SIZE - 1))
		return -EINVAL;

	spin_lock_irq(&bp->lock);

	bp->rx_pending = ering->rx_pending;
	bp->tx_pending = ering->tx_pending;

	b44_halt(bp);
	b44_init_rings(bp);
	b44_init_hw(bp, B44_FULL_RESET);
	netif_wake_queue(bp->dev);
	spin_unlock_irq(&bp->lock);

	b44_enable_ints(bp);

	return 0;
}