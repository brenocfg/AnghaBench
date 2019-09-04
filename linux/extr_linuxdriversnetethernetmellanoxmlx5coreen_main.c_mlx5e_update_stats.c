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
struct TYPE_2__ {int /*<<< orphan*/  (* update_stats ) (struct mlx5e_priv*) ;} ;

/* Variables and functions */
 int mlx5e_num_stats_grps ; 
 TYPE_1__* mlx5e_stats_grps ; 
 int /*<<< orphan*/  stub1 (struct mlx5e_priv*) ; 

void mlx5e_update_stats(struct mlx5e_priv *priv)
{
	int i;

	for (i = mlx5e_num_stats_grps - 1; i >= 0; i--)
		if (mlx5e_stats_grps[i].update_stats)
			mlx5e_stats_grps[i].update_stats(priv);
}