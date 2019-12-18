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
struct tg3 {int /*<<< orphan*/  lock; struct rtnl_link_stats64 net_stats_prev; int /*<<< orphan*/  hw_stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_COMPLETE ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_get_nstats (struct tg3*,struct rtnl_link_stats64*) ; 

__attribute__((used)) static void tg3_get_stats64(struct net_device *dev,
			    struct rtnl_link_stats64 *stats)
{
	struct tg3 *tp = netdev_priv(dev);

	spin_lock_bh(&tp->lock);
	if (!tp->hw_stats || !tg3_flag(tp, INIT_COMPLETE)) {
		*stats = tp->net_stats_prev;
		spin_unlock_bh(&tp->lock);
		return;
	}

	tg3_get_nstats(tp, stats);
	spin_unlock_bh(&tp->lock);
}