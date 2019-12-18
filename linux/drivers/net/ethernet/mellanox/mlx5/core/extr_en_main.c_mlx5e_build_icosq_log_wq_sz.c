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
typedef  scalar_t__ u8 ;
struct mlx5e_rq_param {int /*<<< orphan*/  rqc; } ;
struct mlx5e_params {int rq_wq_type; } ;

/* Variables and functions */
 scalar_t__ MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE ; 
 int /*<<< orphan*/  MLX5E_UMR_WQEBBS ; 
#define  MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ 128 
 scalar_t__ mlx5e_get_rq_log_wq_sz (int /*<<< orphan*/ ) ; 
 scalar_t__ order_base_2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 mlx5e_build_icosq_log_wq_sz(struct mlx5e_params *params,
				      struct mlx5e_rq_param *rqp)
{
	switch (params->rq_wq_type) {
	case MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		return order_base_2(MLX5E_UMR_WQEBBS) +
			mlx5e_get_rq_log_wq_sz(rqp->rqc);
	default: /* MLX5_WQ_TYPE_CYCLIC */
		return MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE;
	}
}