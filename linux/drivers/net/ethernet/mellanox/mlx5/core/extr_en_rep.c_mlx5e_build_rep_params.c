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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct mlx5e_rep_priv {struct mlx5_eswitch_rep* rep; } ;
struct mlx5e_params {int num_tc; int tunneled_offload_en; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  tx_min_inline_mode; scalar_t__ rx_dim_enabled; int /*<<< orphan*/  log_sq_size; int /*<<< orphan*/  sw_mtu; int /*<<< orphan*/  hard_mtu; } ;
struct TYPE_2__ {struct mlx5e_params params; } ;
struct mlx5e_priv {int /*<<< orphan*/  rss_params; TYPE_1__ channels; struct mlx5_core_dev* mdev; struct mlx5e_rep_priv* ppriv; } ;
struct mlx5_eswitch_rep {scalar_t__ vport; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_ETH_HARD_MTU ; 
 int /*<<< orphan*/  MLX5E_PARAMS_DEFAULT_LOG_SQ_SIZE ; 
 int /*<<< orphan*/  MLX5E_REP_PARAMS_DEF_LOG_SQ_SIZE ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CQ_PERIOD_MODE_START_FROM_CQE ; 
 int /*<<< orphan*/  MLX5_CQ_PERIOD_MODE_START_FROM_EQE ; 
 scalar_t__ MLX5_VPORT_UPLINK ; 
 int /*<<< orphan*/  cq_moderation ; 
 int /*<<< orphan*/  cq_period_start_from_cqe ; 
 int /*<<< orphan*/  mlx5_query_min_inline (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_rq_params (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 int /*<<< orphan*/  mlx5e_build_rss_params (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_set_rx_cq_mode_params (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx5e_build_rep_params(struct net_device *netdev)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep = rpriv->rep;
	struct mlx5_core_dev *mdev = priv->mdev;
	struct mlx5e_params *params;

	u8 cq_period_mode = MLX5_CAP_GEN(mdev, cq_period_start_from_cqe) ?
					 MLX5_CQ_PERIOD_MODE_START_FROM_CQE :
					 MLX5_CQ_PERIOD_MODE_START_FROM_EQE;

	params = &priv->channels.params;
	params->hard_mtu    = MLX5E_ETH_HARD_MTU;
	params->sw_mtu      = netdev->mtu;

	/* SQ */
	if (rep->vport == MLX5_VPORT_UPLINK)
		params->log_sq_size = MLX5E_PARAMS_DEFAULT_LOG_SQ_SIZE;
	else
		params->log_sq_size = MLX5E_REP_PARAMS_DEF_LOG_SQ_SIZE;

	/* RQ */
	mlx5e_build_rq_params(mdev, params);

	/* CQ moderation params */
	params->rx_dim_enabled = MLX5_CAP_GEN(mdev, cq_moderation);
	mlx5e_set_rx_cq_mode_params(params, cq_period_mode);

	params->num_tc                = 1;
	params->tunneled_offload_en = false;

	mlx5_query_min_inline(mdev, &params->tx_min_inline_mode);

	/* RSS */
	mlx5e_build_rss_params(&priv->rss_params, params->num_channels);
}