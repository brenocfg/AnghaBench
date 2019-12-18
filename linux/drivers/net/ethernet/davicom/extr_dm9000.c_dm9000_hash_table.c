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
struct board_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm9000_hash_table_unlocked (struct net_device*) ; 
 struct board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
dm9000_hash_table(struct net_device *dev)
{
	struct board_info *db = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&db->lock, flags);
	dm9000_hash_table_unlocked(dev);
	spin_unlock_irqrestore(&db->lock, flags);
}