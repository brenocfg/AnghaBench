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
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
#define  IFLA_OFFLOAD_XSTATS_CPU_HIT 128 
 int /*<<< orphan*/  mlx5e_is_uplink_rep (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_is_vf_vport_rep (struct mlx5e_priv*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device const*) ; 

bool mlx5e_has_offload_stats(const struct net_device *dev, int attr_id)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	switch (attr_id) {
	case IFLA_OFFLOAD_XSTATS_CPU_HIT:
		if (mlx5e_is_vf_vport_rep(priv) || mlx5e_is_uplink_rep(priv))
			return true;
	}

	return false;
}