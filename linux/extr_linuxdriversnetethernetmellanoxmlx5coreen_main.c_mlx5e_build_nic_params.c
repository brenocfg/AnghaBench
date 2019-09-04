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
typedef  void* u16 ;
struct mlx5e_params {int num_tc; int rx_cqe_compress_def; scalar_t__ rq_wq_type; int lro_en; int /*<<< orphan*/  indirection_rqt; int /*<<< orphan*/  toeplitz_hash_key; int /*<<< orphan*/  rss_hfunc; int /*<<< orphan*/  tx_min_inline_mode; void* tx_dim_enabled; void* rx_dim_enabled; int /*<<< orphan*/  lro_timeout; int /*<<< orphan*/  log_sq_size; void* num_channels; int /*<<< orphan*/  hard_mtu; void* sw_mtu; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RSS_HASH_XOR ; 
 int /*<<< orphan*/  MLX5E_DEFAULT_LRO_TIMEOUT ; 
 int /*<<< orphan*/  MLX5E_ETH_HARD_MTU ; 
 int /*<<< orphan*/  MLX5E_INDIR_RQT_SIZE ; 
 int /*<<< orphan*/  MLX5E_PARAMS_DEFAULT_LOG_SQ_SIZE ; 
 int /*<<< orphan*/  MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_CQE_COMPRESS ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_STRIDING_RQ ; 
 int /*<<< orphan*/  MLX5E_SET_PFLAG (struct mlx5e_params*,int /*<<< orphan*/ ,int) ; 
 void* MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CQ_PERIOD_MODE_START_FROM_CQE ; 
 int /*<<< orphan*/  MLX5_CQ_PERIOD_MODE_START_FROM_EQE ; 
 scalar_t__ MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ ; 
 int /*<<< orphan*/  cq_moderation ; 
 int /*<<< orphan*/  cq_period_start_from_cqe ; 
 int /*<<< orphan*/  cqe_compression ; 
 scalar_t__ is_kdump_kernel () ; 
 int /*<<< orphan*/  mlx5e_build_default_indir_rqt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mlx5e_choose_lro_timeout (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_init_rq_type_params (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 int /*<<< orphan*/  mlx5e_params_calculate_tx_min_inline (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5e_rx_is_linear_skb (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 scalar_t__ mlx5e_rx_mpwqe_is_linear_skb (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 int /*<<< orphan*/  mlx5e_set_rq_type (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 int /*<<< orphan*/  mlx5e_set_rx_cq_mode_params (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_set_tx_cq_mode_params (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5e_striding_rq_possible (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int /*<<< orphan*/ ,int) ; 
 int slow_pci_heuristic (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  vport_group_manager ; 

void mlx5e_build_nic_params(struct mlx5_core_dev *mdev,
			    struct mlx5e_params *params,
			    u16 max_channels, u16 mtu)
{
	u8 rx_cq_period_mode;

	params->sw_mtu = mtu;
	params->hard_mtu = MLX5E_ETH_HARD_MTU;
	params->num_channels = max_channels;
	params->num_tc       = 1;

	/* SQ */
	params->log_sq_size = is_kdump_kernel() ?
		MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE :
		MLX5E_PARAMS_DEFAULT_LOG_SQ_SIZE;

	/* set CQE compression */
	params->rx_cqe_compress_def = false;
	if (MLX5_CAP_GEN(mdev, cqe_compression) &&
	    MLX5_CAP_GEN(mdev, vport_group_manager))
		params->rx_cqe_compress_def = slow_pci_heuristic(mdev);

	MLX5E_SET_PFLAG(params, MLX5E_PFLAG_RX_CQE_COMPRESS, params->rx_cqe_compress_def);

	/* RQ */
	/* Prefer Striding RQ, unless any of the following holds:
	 * - Striding RQ configuration is not possible/supported.
	 * - Slow PCI heuristic.
	 * - Legacy RQ would use linear SKB while Striding RQ would use non-linear.
	 */
	if (!slow_pci_heuristic(mdev) &&
	    mlx5e_striding_rq_possible(mdev, params) &&
	    (mlx5e_rx_mpwqe_is_linear_skb(mdev, params) ||
	     !mlx5e_rx_is_linear_skb(mdev, params)))
		MLX5E_SET_PFLAG(params, MLX5E_PFLAG_RX_STRIDING_RQ, true);
	mlx5e_set_rq_type(mdev, params);
	mlx5e_init_rq_type_params(mdev, params);

	/* HW LRO */

	/* TODO: && MLX5_CAP_ETH(mdev, lro_cap) */
	if (params->rq_wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ)
		if (!mlx5e_rx_mpwqe_is_linear_skb(mdev, params))
			params->lro_en = !slow_pci_heuristic(mdev);
	params->lro_timeout = mlx5e_choose_lro_timeout(mdev, MLX5E_DEFAULT_LRO_TIMEOUT);

	/* CQ moderation params */
	rx_cq_period_mode = MLX5_CAP_GEN(mdev, cq_period_start_from_cqe) ?
			MLX5_CQ_PERIOD_MODE_START_FROM_CQE :
			MLX5_CQ_PERIOD_MODE_START_FROM_EQE;
	params->rx_dim_enabled = MLX5_CAP_GEN(mdev, cq_moderation);
	params->tx_dim_enabled = MLX5_CAP_GEN(mdev, cq_moderation);
	mlx5e_set_rx_cq_mode_params(params, rx_cq_period_mode);
	mlx5e_set_tx_cq_mode_params(params, MLX5_CQ_PERIOD_MODE_START_FROM_EQE);

	/* TX inline */
	params->tx_min_inline_mode = mlx5e_params_calculate_tx_min_inline(mdev);

	/* RSS */
	params->rss_hfunc = ETH_RSS_HASH_XOR;
	netdev_rss_key_fill(params->toeplitz_hash_key, sizeof(params->toeplitz_hash_key));
	mlx5e_build_default_indir_rqt(params->indirection_rqt,
				      MLX5E_INDIR_RQT_SIZE, max_channels);
}