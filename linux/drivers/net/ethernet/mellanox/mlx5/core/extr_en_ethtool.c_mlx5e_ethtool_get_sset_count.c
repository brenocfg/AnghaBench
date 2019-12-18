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
struct mlx5e_priv {int dummy; } ;
struct TYPE_2__ {int (* get_num_stats ) (struct mlx5e_priv*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_PRIV_FLAGS 130 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int MLX5E_NUM_PFLAGS ; 
 int mlx5e_num_stats_grps ; 
 int mlx5e_self_test_num (struct mlx5e_priv*) ; 
 TYPE_1__* mlx5e_stats_grps ; 
 int stub1 (struct mlx5e_priv*) ; 

int mlx5e_ethtool_get_sset_count(struct mlx5e_priv *priv, int sset)
{
	int i, num_stats = 0;

	switch (sset) {
	case ETH_SS_STATS:
		for (i = 0; i < mlx5e_num_stats_grps; i++)
			num_stats += mlx5e_stats_grps[i].get_num_stats(priv);
		return num_stats;
	case ETH_SS_PRIV_FLAGS:
		return MLX5E_NUM_PFLAGS;
	case ETH_SS_TEST:
		return mlx5e_self_test_num(priv);
	/* fallthrough */
	default:
		return -EOPNOTSUPP;
	}
}