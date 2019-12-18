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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct mlx5_pme_stats {int /*<<< orphan*/  error_counters; int /*<<< orphan*/  status_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_READ_CTR64_CPU (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int NUM_PME_ERR_STATS ; 
 int NUM_PME_STATUS_STATS ; 
 int /*<<< orphan*/  mlx5_get_pme_stats (int /*<<< orphan*/ ,struct mlx5_pme_stats*) ; 
 int /*<<< orphan*/  mlx5e_pme_error_desc ; 
 int /*<<< orphan*/  mlx5e_pme_status_desc ; 

__attribute__((used)) static int mlx5e_grp_pme_fill_stats(struct mlx5e_priv *priv, u64 *data,
				    int idx)
{
	struct mlx5_pme_stats pme_stats;
	int i;

	mlx5_get_pme_stats(priv->mdev, &pme_stats);

	for (i = 0; i < NUM_PME_STATUS_STATS; i++)
		data[idx++] = MLX5E_READ_CTR64_CPU(pme_stats.status_counters,
						   mlx5e_pme_status_desc, i);

	for (i = 0; i < NUM_PME_ERR_STATS; i++)
		data[idx++] = MLX5E_READ_CTR64_CPU(pme_stats.error_counters,
						   mlx5e_pme_error_desc, i);

	return idx;
}