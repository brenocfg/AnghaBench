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
struct TYPE_2__ {scalar_t__ trust_state; } ;
struct mlx5e_priv {TYPE_1__ dcbx_dp; int /*<<< orphan*/  mdev; } ;
struct mlx5e_params {scalar_t__ tx_min_inline_mode; } ;

/* Variables and functions */
 scalar_t__ MLX5_INLINE_MODE_IP ; 
 scalar_t__ MLX5_INLINE_MODE_L2 ; 
 scalar_t__ MLX5_QPTS_TRUST_DSCP ; 
 int /*<<< orphan*/  mlx5_query_min_inline (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void mlx5e_trust_update_tx_min_inline_mode(struct mlx5e_priv *priv,
						  struct mlx5e_params *params)
{
	mlx5_query_min_inline(priv->mdev, &params->tx_min_inline_mode);
	if (priv->dcbx_dp.trust_state == MLX5_QPTS_TRUST_DSCP &&
	    params->tx_min_inline_mode == MLX5_INLINE_MODE_L2)
		params->tx_min_inline_mode = MLX5_INLINE_MODE_IP;
}