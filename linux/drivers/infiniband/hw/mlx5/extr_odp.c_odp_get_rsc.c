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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_core_rsc_common {int dummy; } ;
struct mlx5_core_srq {struct mlx5_core_rsc_common common; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_RES_QP ; 
#define  MLX5_WQE_PF_TYPE_REQ_READ_OR_ATOMIC 131 
#define  MLX5_WQE_PF_TYPE_REQ_SEND_OR_WRITE 130 
#define  MLX5_WQE_PF_TYPE_RESP 129 
#define  MLX5_WQE_PF_TYPE_RMP 128 
 struct mlx5_core_srq* mlx5_cmd_get_srq (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 struct mlx5_core_rsc_common* mlx5_core_res_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mlx5_core_rsc_common *odp_get_rsc(struct mlx5_ib_dev *dev,
						       u32 wq_num, int pf_type)
{
	struct mlx5_core_rsc_common *common = NULL;
	struct mlx5_core_srq *srq;

	switch (pf_type) {
	case MLX5_WQE_PF_TYPE_RMP:
		srq = mlx5_cmd_get_srq(dev, wq_num);
		if (srq)
			common = &srq->common;
		break;
	case MLX5_WQE_PF_TYPE_REQ_SEND_OR_WRITE:
	case MLX5_WQE_PF_TYPE_RESP:
	case MLX5_WQE_PF_TYPE_REQ_READ_OR_ATOMIC:
		common = mlx5_core_res_hold(dev->mdev, wq_num, MLX5_RES_QP);
		break;
	default:
		break;
	}

	return common;
}