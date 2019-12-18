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
struct mlx5e_dcbx {scalar_t__ mode; int cap; int manual_buffer; int /*<<< orphan*/  cable_len; } ;
struct mlx5e_priv {struct mlx5e_dcbx dcbx; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int DCB_CAP_DCBX_HOST ; 
 int DCB_CAP_DCBX_VER_CEE ; 
 int DCB_CAP_DCBX_VER_IEEE ; 
 scalar_t__ MLX5E_DCBX_PARAM_VER_OPER_HOST ; 
 int /*<<< orphan*/  MLX5E_DEFAULT_CABLE_LEN ; 
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,struct mlx5e_dcbx*) ; 
 int /*<<< orphan*/  mlx5e_dcbnl_query_dcbx_mode (struct mlx5e_priv*,scalar_t__*) ; 
 int /*<<< orphan*/  mlx5e_ets_init (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_trust_initialize (struct mlx5e_priv*) ; 
 struct mlx5e_dcbx* qos ; 

void mlx5e_dcbnl_initialize(struct mlx5e_priv *priv)
{
	struct mlx5e_dcbx *dcbx = &priv->dcbx;

	mlx5e_trust_initialize(priv);

	if (!MLX5_CAP_GEN(priv->mdev, qos))
		return;

	if (MLX5_CAP_GEN(priv->mdev, dcbx))
		mlx5e_dcbnl_query_dcbx_mode(priv, &dcbx->mode);

	priv->dcbx.cap = DCB_CAP_DCBX_VER_CEE |
			 DCB_CAP_DCBX_VER_IEEE;
	if (priv->dcbx.mode == MLX5E_DCBX_PARAM_VER_OPER_HOST)
		priv->dcbx.cap |= DCB_CAP_DCBX_HOST;

	priv->dcbx.manual_buffer = false;
	priv->dcbx.cable_len = MLX5E_DEFAULT_CABLE_LEN;

	mlx5e_ets_init(priv);
}