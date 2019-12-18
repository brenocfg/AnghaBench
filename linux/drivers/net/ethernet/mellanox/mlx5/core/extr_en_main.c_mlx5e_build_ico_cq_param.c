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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5e_priv {int dummy; } ;
struct mlx5e_cq_param {int /*<<< orphan*/  cq_period_mode; void* cqc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_CQ_PERIOD_MODE_START_FROM_EQE ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_cq_size ; 
 int /*<<< orphan*/  mlx5e_build_common_cq_param (struct mlx5e_priv*,struct mlx5e_cq_param*) ; 

void mlx5e_build_ico_cq_param(struct mlx5e_priv *priv,
			      u8 log_wq_size,
			      struct mlx5e_cq_param *param)
{
	void *cqc = param->cqc;

	MLX5_SET(cqc, cqc, log_cq_size, log_wq_size);

	mlx5e_build_common_cq_param(priv, param);

	param->cq_period_mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;
}