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
struct TYPE_3__ {int /*<<< orphan*/  query_vnic_env_out; } ;
struct TYPE_4__ {TYPE_1__ vnic; } ;
struct mlx5e_priv {TYPE_2__ stats; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_READ_CTR32_BE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5E_READ_CTR64_BE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int NUM_VNIC_ENV_DEV_OOB_COUNTERS (int /*<<< orphan*/ ) ; 
 int NUM_VNIC_ENV_STEER_COUNTERS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_env_stats_dev_oob_desc ; 
 int /*<<< orphan*/  vnic_env_stats_steer_desc ; 

__attribute__((used)) static int mlx5e_grp_vnic_env_fill_stats(struct mlx5e_priv *priv, u64 *data,
					 int idx)
{
	int i;

	for (i = 0; i < NUM_VNIC_ENV_STEER_COUNTERS(priv->mdev); i++)
		data[idx++] = MLX5E_READ_CTR64_BE(priv->stats.vnic.query_vnic_env_out,
						  vnic_env_stats_steer_desc, i);

	for (i = 0; i < NUM_VNIC_ENV_DEV_OOB_COUNTERS(priv->mdev); i++)
		data[idx++] = MLX5E_READ_CTR32_BE(priv->stats.vnic.query_vnic_env_out,
						  vnic_env_stats_dev_oob_desc, i);
	return idx;
}