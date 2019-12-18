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
struct net_device {int /*<<< orphan*/  stats; } ;
struct mlx4_en_priv {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_en_fold_software_stats (struct net_device*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_stats_to_stats64 (struct rtnl_link_stats64*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx4_en_get_stats64(struct net_device *dev, struct rtnl_link_stats64 *stats)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	spin_lock_bh(&priv->stats_lock);
	mlx4_en_fold_software_stats(dev);
	netdev_stats_to_stats64(stats, &dev->stats);
	spin_unlock_bh(&priv->stats_lock);
}