#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtnl_link_stats64 {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vf_vport; } ;
struct mlx5e_priv {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct rtnl_link_stats64*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5e_queue_update_stats (struct mlx5e_priv*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
mlx5e_rep_get_stats(struct net_device *dev, struct rtnl_link_stats64 *stats)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	/* update HW stats in background for next time */
	mlx5e_queue_update_stats(priv);
	memcpy(stats, &priv->stats.vf_vport, sizeof(*stats));
}