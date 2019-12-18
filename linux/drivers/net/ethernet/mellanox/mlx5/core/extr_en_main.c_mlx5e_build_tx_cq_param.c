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
struct TYPE_2__ {int /*<<< orphan*/  cq_period_mode; } ;
struct mlx5e_params {TYPE_1__ tx_cq_moderation; int /*<<< orphan*/  log_sq_size; } ;
struct mlx5e_cq_param {int /*<<< orphan*/  cq_period_mode; void* cqc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_cq_size ; 
 int /*<<< orphan*/  mlx5e_build_common_cq_param (struct mlx5e_priv*,struct mlx5e_cq_param*) ; 

void mlx5e_build_tx_cq_param(struct mlx5e_priv *priv,
			     struct mlx5e_params *params,
			     struct mlx5e_cq_param *param)
{
	void *cqc = param->cqc;

	MLX5_SET(cqc, cqc, log_cq_size, params->log_sq_size);

	mlx5e_build_common_cq_param(priv, param);
	param->cq_period_mode = params->tx_cq_moderation.cq_period_mode;
}