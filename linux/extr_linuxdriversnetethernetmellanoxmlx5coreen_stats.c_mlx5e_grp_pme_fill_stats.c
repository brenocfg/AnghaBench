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
struct mlx5e_priv {TYPE_1__* mdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  error_counters; int /*<<< orphan*/  status_counters; } ;
struct mlx5_priv {TYPE_2__ pme_stats; } ;
struct TYPE_3__ {struct mlx5_priv priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_READ_CTR64_CPU (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int NUM_PME_ERR_STATS ; 
 int NUM_PME_STATUS_STATS ; 
 int /*<<< orphan*/  mlx5e_pme_error_desc ; 
 int /*<<< orphan*/  mlx5e_pme_status_desc ; 

__attribute__((used)) static int mlx5e_grp_pme_fill_stats(struct mlx5e_priv *priv, u64 *data,
				    int idx)
{
	struct mlx5_priv *mlx5_priv = &priv->mdev->priv;
	int i;

	for (i = 0; i < NUM_PME_STATUS_STATS; i++)
		data[idx++] = MLX5E_READ_CTR64_CPU(mlx5_priv->pme_stats.status_counters,
						   mlx5e_pme_status_desc, i);

	for (i = 0; i < NUM_PME_ERR_STATS; i++)
		data[idx++] = MLX5E_READ_CTR64_CPU(mlx5_priv->pme_stats.error_counters,
						   mlx5e_pme_error_desc, i);

	return idx;
}