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
struct mlx5e_params {int dummy; } ;
struct mlx5e_channel_param {int /*<<< orphan*/  icosq_cq; int /*<<< orphan*/  tx_cq; int /*<<< orphan*/  rx_cq; int /*<<< orphan*/  icosq; int /*<<< orphan*/  xdp_sq; int /*<<< orphan*/  sq; int /*<<< orphan*/  rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_build_ico_cq_param (struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_icosq_log_wq_sz (struct mlx5e_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_icosq_param (struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_rq_param (struct mlx5e_priv*,struct mlx5e_params*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_rx_cq_param (struct mlx5e_priv*,struct mlx5e_params*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_sq_param (struct mlx5e_priv*,struct mlx5e_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_tx_cq_param (struct mlx5e_priv*,struct mlx5e_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_xdpsq_param (struct mlx5e_priv*,struct mlx5e_params*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_build_channel_param(struct mlx5e_priv *priv,
				      struct mlx5e_params *params,
				      struct mlx5e_channel_param *cparam)
{
	u8 icosq_log_wq_sz;

	mlx5e_build_rq_param(priv, params, NULL, &cparam->rq);

	icosq_log_wq_sz = mlx5e_build_icosq_log_wq_sz(params, &cparam->rq);

	mlx5e_build_sq_param(priv, params, &cparam->sq);
	mlx5e_build_xdpsq_param(priv, params, &cparam->xdp_sq);
	mlx5e_build_icosq_param(priv, icosq_log_wq_sz, &cparam->icosq);
	mlx5e_build_rx_cq_param(priv, params, NULL, &cparam->rx_cq);
	mlx5e_build_tx_cq_param(priv, params, &cparam->tx_cq);
	mlx5e_build_ico_cq_param(priv, icosq_log_wq_sz, &cparam->icosq_cq);
}