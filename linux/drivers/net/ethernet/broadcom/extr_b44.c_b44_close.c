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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  phydev; } ;
struct b44 {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int B44_FLAG_EXTERNAL_PHY ; 
 int B44_FLAG_WOL_ENABLE ; 
 int /*<<< orphan*/  B44_PARTIAL_RESET ; 
 int /*<<< orphan*/  b44_free_consistent (struct b44*) ; 
 int /*<<< orphan*/  b44_free_rings (struct b44*) ; 
 int /*<<< orphan*/  b44_halt (struct b44*) ; 
 int /*<<< orphan*/  b44_init_hw (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_setup_wol (struct b44*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b44_close(struct net_device *dev)
{
	struct b44 *bp = netdev_priv(dev);

	netif_stop_queue(dev);

	if (bp->flags & B44_FLAG_EXTERNAL_PHY)
		phy_stop(dev->phydev);

	napi_disable(&bp->napi);

	del_timer_sync(&bp->timer);

	spin_lock_irq(&bp->lock);

	b44_halt(bp);
	b44_free_rings(bp);
	netif_carrier_off(dev);

	spin_unlock_irq(&bp->lock);

	free_irq(dev->irq, dev);

	if (bp->flags & B44_FLAG_WOL_ENABLE) {
		b44_init_hw(bp, B44_PARTIAL_RESET);
		b44_setup_wol(bp);
	}

	b44_free_consistent(bp);

	return 0;
}