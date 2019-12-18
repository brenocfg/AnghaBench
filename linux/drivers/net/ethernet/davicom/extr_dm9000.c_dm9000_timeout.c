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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct board_info {int in_timeout; int /*<<< orphan*/  lock; int /*<<< orphan*/  io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm9000_init_dm9000 (struct net_device*) ; 
 int /*<<< orphan*/  dm9000_unmask_interrupts (struct board_info*) ; 
 struct board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm9000_timeout(struct net_device *dev)
{
	struct board_info *db = netdev_priv(dev);
	u8 reg_save;
	unsigned long flags;

	/* Save previous register address */
	spin_lock_irqsave(&db->lock, flags);
	db->in_timeout = 1;
	reg_save = readb(db->io_addr);

	netif_stop_queue(dev);
	dm9000_init_dm9000(dev);
	dm9000_unmask_interrupts(db);
	/* We can accept TX packets again */
	netif_trans_update(dev); /* prevent tx timeout */
	netif_wake_queue(dev);

	/* Restore previous register address */
	writeb(reg_save, db->io_addr);
	db->in_timeout = 0;
	spin_unlock_irqrestore(&db->lock, flags);
}