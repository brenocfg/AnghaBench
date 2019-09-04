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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_2__ {int (* fill_stats ) (struct mlx5e_priv*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int mlx5e_num_stats_grps ; 
 TYPE_1__* mlx5e_stats_grps ; 
 int /*<<< orphan*/  mlx5e_update_stats (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct mlx5e_priv*,int /*<<< orphan*/ *,int) ; 

void mlx5e_ethtool_get_ethtool_stats(struct mlx5e_priv *priv,
				     struct ethtool_stats *stats, u64 *data)
{
	int i, idx = 0;

	mutex_lock(&priv->state_lock);
	mlx5e_update_stats(priv);
	mutex_unlock(&priv->state_lock);

	for (i = 0; i < mlx5e_num_stats_grps; i++)
		idx = mlx5e_stats_grps[i].fill_stats(priv, data, idx);
}