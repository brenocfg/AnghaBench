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
struct mlx5e_dcbx {scalar_t__ mode; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; struct mlx5e_dcbx dcbx; } ;

/* Variables and functions */
 scalar_t__ MLX5E_DCBX_PARAM_VER_OPER_HOST ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,struct mlx5e_dcbx*) ; 
 int mlx5e_dcbnl_set_dcbx_mode (struct mlx5e_priv*,scalar_t__) ; 

__attribute__((used)) static int mlx5e_dcbnl_switch_to_host_mode(struct mlx5e_priv *priv)
{
	struct mlx5e_dcbx *dcbx = &priv->dcbx;
	int err;

	if (!MLX5_CAP_GEN(priv->mdev, dcbx))
		return 0;

	if (dcbx->mode == MLX5E_DCBX_PARAM_VER_OPER_HOST)
		return 0;

	err = mlx5e_dcbnl_set_dcbx_mode(priv, MLX5E_DCBX_PARAM_VER_OPER_HOST);
	if (err)
		return err;

	dcbx->mode = MLX5E_DCBX_PARAM_VER_OPER_HOST;
	return 0;
}