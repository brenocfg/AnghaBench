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
struct mlx5e_sq_param {void* sqc; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct mlx5e_params {int log_sq_size; } ;

/* Variables and functions */
 void* MLX5_ADDR_OF (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_IPSEC_DEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int,int) ; 
 int log_wq_sz ; 
 scalar_t__ mlx5_geneve_tx_allowed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_build_sq_param_common (struct mlx5e_priv*,struct mlx5e_sq_param*) ; 
 void* wq ; 

__attribute__((used)) static void mlx5e_build_sq_param(struct mlx5e_priv *priv,
				 struct mlx5e_params *params,
				 struct mlx5e_sq_param *param)
{
	void *sqc = param->sqc;
	void *wq = MLX5_ADDR_OF(sqc, sqc, wq);
	bool allow_swp;

	allow_swp = mlx5_geneve_tx_allowed(priv->mdev) ||
		    !!MLX5_IPSEC_DEV(priv->mdev);
	mlx5e_build_sq_param_common(priv, param);
	MLX5_SET(wq, wq, log_wq_sz, params->log_sq_size);
	MLX5_SET(sqc, sqc, allow_swp, allow_swp);
}