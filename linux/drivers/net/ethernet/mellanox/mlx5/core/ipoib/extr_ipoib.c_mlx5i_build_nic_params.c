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
struct mlx5e_params {int lro_en; int tunneled_offload_en; scalar_t__ hard_mtu; int /*<<< orphan*/  log_rq_mtu_frames; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_STRIDING_RQ ; 
 int /*<<< orphan*/  MLX5E_SET_PFLAG (struct mlx5e_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5I_PARAMS_DEFAULT_LOG_RQ_SIZE ; 
 scalar_t__ MLX5_IB_GRH_BYTES ; 
 scalar_t__ MLX5_IPOIB_HARD_LEN ; 
 scalar_t__ is_kdump_kernel () ; 
 int /*<<< orphan*/  mlx5e_init_rq_type_params (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 int /*<<< orphan*/  mlx5e_set_rq_type (struct mlx5_core_dev*,struct mlx5e_params*) ; 

__attribute__((used)) static void mlx5i_build_nic_params(struct mlx5_core_dev *mdev,
				   struct mlx5e_params *params)
{
	/* Override RQ params as IPoIB supports only LINKED LIST RQ for now */
	MLX5E_SET_PFLAG(params, MLX5E_PFLAG_RX_STRIDING_RQ, false);
	mlx5e_set_rq_type(mdev, params);
	mlx5e_init_rq_type_params(mdev, params);

	/* RQ size in ipoib by default is 512 */
	params->log_rq_mtu_frames = is_kdump_kernel() ?
		MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE :
		MLX5I_PARAMS_DEFAULT_LOG_RQ_SIZE;

	params->lro_en = false;
	params->hard_mtu = MLX5_IB_GRH_BYTES + MLX5_IPOIB_HARD_LEN;
	params->tunneled_offload_en = false;
}