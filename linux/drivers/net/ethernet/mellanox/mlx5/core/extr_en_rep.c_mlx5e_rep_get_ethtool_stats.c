#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vf_vport; int /*<<< orphan*/  sw; } ;
struct mlx5e_priv {TYPE_2__ stats; int /*<<< orphan*/  state_lock; TYPE_1__* profile; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_stats ) (struct mlx5e_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_READ_CTR64_CPU (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int NUM_VPORT_REP_HW_COUNTERS ; 
 int NUM_VPORT_REP_SW_COUNTERS ; 
 int /*<<< orphan*/  mlx5e_rep_update_sw_counters (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  sw_rep_stats_desc ; 
 int /*<<< orphan*/  vport_rep_stats_desc ; 

__attribute__((used)) static void mlx5e_rep_get_ethtool_stats(struct net_device *dev,
					struct ethtool_stats *stats, u64 *data)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	int i, j;

	if (!data)
		return;

	mutex_lock(&priv->state_lock);
	mlx5e_rep_update_sw_counters(priv);
	priv->profile->update_stats(priv);
	mutex_unlock(&priv->state_lock);

	for (i = 0; i < NUM_VPORT_REP_SW_COUNTERS; i++)
		data[i] = MLX5E_READ_CTR64_CPU(&priv->stats.sw,
					       sw_rep_stats_desc, i);

	for (j = 0; j < NUM_VPORT_REP_HW_COUNTERS; j++, i++)
		data[i] = MLX5E_READ_CTR64_CPU(&priv->stats.vf_vport,
					       vport_rep_stats_desc, j);
}