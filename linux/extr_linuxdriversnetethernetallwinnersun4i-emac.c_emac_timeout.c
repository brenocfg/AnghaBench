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
struct emac_board_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  emac_init_device (struct net_device*) ; 
 int /*<<< orphan*/  emac_reset (struct emac_board_info*) ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_timer (struct emac_board_info*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void emac_timeout(struct net_device *dev)
{
	struct emac_board_info *db = netdev_priv(dev);
	unsigned long flags;

	if (netif_msg_timer(db))
		dev_err(db->dev, "tx time out.\n");

	/* Save previous register address */
	spin_lock_irqsave(&db->lock, flags);

	netif_stop_queue(dev);
	emac_reset(db);
	emac_init_device(dev);
	/* We can accept TX packets again */
	netif_trans_update(dev);
	netif_wake_queue(dev);

	/* Restore previous register address */
	spin_unlock_irqrestore(&db->lock, flags);
}