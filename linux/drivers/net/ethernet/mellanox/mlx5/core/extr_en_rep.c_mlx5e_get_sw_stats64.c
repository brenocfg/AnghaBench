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
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_fold_sw_stats64 (struct mlx5e_priv*,struct rtnl_link_stats64*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int
mlx5e_get_sw_stats64(const struct net_device *dev,
		     struct rtnl_link_stats64 *stats)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	mlx5e_fold_sw_stats64(priv, stats);
	return 0;
}