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
struct rtnl_link_stats64 {int dummy; } ;
struct net_device {int dummy; } ;
struct bnad {int /*<<< orphan*/  bna_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnad_netdev_hwstats_fill (struct bnad*,struct rtnl_link_stats64*) ; 
 int /*<<< orphan*/  bnad_netdev_qstats_fill (struct bnad*,struct rtnl_link_stats64*) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
bnad_get_stats64(struct net_device *netdev, struct rtnl_link_stats64 *stats)
{
	struct bnad *bnad = netdev_priv(netdev);
	unsigned long flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);

	bnad_netdev_qstats_fill(bnad, stats);
	bnad_netdev_hwstats_fill(bnad, stats);

	spin_unlock_irqrestore(&bnad->bna_lock, flags);
}