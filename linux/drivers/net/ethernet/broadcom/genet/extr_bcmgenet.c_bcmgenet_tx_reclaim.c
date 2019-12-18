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
struct bcmgenet_tx_ring {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int __bcmgenet_tx_reclaim (struct net_device*,struct bcmgenet_tx_ring*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int bcmgenet_tx_reclaim(struct net_device *dev,
				struct bcmgenet_tx_ring *ring)
{
	unsigned int released;

	spin_lock_bh(&ring->lock);
	released = __bcmgenet_tx_reclaim(dev, ring);
	spin_unlock_bh(&ring->lock);

	return released;
}