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
struct mlx5e_params {scalar_t__ rq_wq_type; int /*<<< orphan*/  log_rq_mtu_frames; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_GET_PFLAG (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_PARAMS_DEFAULT_LOG_RQ_SIZE ; 
 int /*<<< orphan*/  MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_CQE_COMPRESS ; 
 scalar_t__ MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ ; 
 scalar_t__ is_kdump_kernel () ; 
 int /*<<< orphan*/  mlx5_core_info (struct mlx5_core_dev*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_mpwqe_get_log_rq_size (struct mlx5e_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_mpwqe_get_log_stride_size (struct mlx5_core_dev*,struct mlx5e_params*,int /*<<< orphan*/ *) ; 

void mlx5e_init_rq_type_params(struct mlx5_core_dev *mdev,
			       struct mlx5e_params *params)
{
	params->log_rq_mtu_frames = is_kdump_kernel() ?
		MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE :
		MLX5E_PARAMS_DEFAULT_LOG_RQ_SIZE;

	mlx5_core_info(mdev, "MLX5E: StrdRq(%d) RqSz(%ld) StrdSz(%ld) RxCqeCmprss(%d)\n",
		       params->rq_wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ,
		       params->rq_wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ ?
		       BIT(mlx5e_mpwqe_get_log_rq_size(params, NULL)) :
		       BIT(params->log_rq_mtu_frames),
		       BIT(mlx5e_mpwqe_get_log_stride_size(mdev, params, NULL)),
		       MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_CQE_COMPRESS));
}