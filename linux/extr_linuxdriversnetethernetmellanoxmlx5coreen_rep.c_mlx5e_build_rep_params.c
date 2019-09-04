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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5e_params {int num_tc; int /*<<< orphan*/  tx_min_inline_mode; int /*<<< orphan*/  lro_wqe_sz; scalar_t__ rx_dim_enabled; int /*<<< orphan*/  log_rq_mtu_frames; int /*<<< orphan*/  rq_wq_type; int /*<<< orphan*/  log_sq_size; int /*<<< orphan*/  sw_mtu; int /*<<< orphan*/  hard_mtu; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_ETH_HARD_MTU ; 
 int /*<<< orphan*/  MLX5E_PARAMS_DEFAULT_LRO_WQE_SZ ; 
 int /*<<< orphan*/  MLX5E_REP_PARAMS_LOG_RQ_SIZE ; 
 int /*<<< orphan*/  MLX5E_REP_PARAMS_LOG_SQ_SIZE ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CQ_PERIOD_MODE_START_FROM_CQE ; 
 int /*<<< orphan*/  MLX5_CQ_PERIOD_MODE_START_FROM_EQE ; 
 int /*<<< orphan*/  MLX5_WQ_TYPE_CYCLIC ; 
 int /*<<< orphan*/  cq_moderation ; 
 int /*<<< orphan*/  cq_period_start_from_cqe ; 
 int /*<<< orphan*/  mlx5_query_min_inline (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_set_rx_cq_mode_params (struct mlx5e_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_build_rep_params(struct mlx5_core_dev *mdev,
				   struct mlx5e_params *params, u16 mtu)
{
	u8 cq_period_mode = MLX5_CAP_GEN(mdev, cq_period_start_from_cqe) ?
					 MLX5_CQ_PERIOD_MODE_START_FROM_CQE :
					 MLX5_CQ_PERIOD_MODE_START_FROM_EQE;

	params->hard_mtu    = MLX5E_ETH_HARD_MTU;
	params->sw_mtu      = mtu;
	params->log_sq_size = MLX5E_REP_PARAMS_LOG_SQ_SIZE;
	params->rq_wq_type  = MLX5_WQ_TYPE_CYCLIC;
	params->log_rq_mtu_frames = MLX5E_REP_PARAMS_LOG_RQ_SIZE;

	params->rx_dim_enabled = MLX5_CAP_GEN(mdev, cq_moderation);
	mlx5e_set_rx_cq_mode_params(params, cq_period_mode);

	params->num_tc                = 1;
	params->lro_wqe_sz            = MLX5E_PARAMS_DEFAULT_LRO_WQE_SZ;

	mlx5_query_min_inline(mdev, &params->tx_min_inline_mode);
}