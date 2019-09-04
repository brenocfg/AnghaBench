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
typedef  int u8 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_CQE_RES_FORMAT_CSUM ; 
 int MLX5_CQE_RES_FORMAT_CSUM_STRIDX ; 
 int MLX5_CQE_RES_FORMAT_HASH ; 
#define  MLX5_IB_CQE_RES_FORMAT_CSUM 130 
#define  MLX5_IB_CQE_RES_FORMAT_CSUM_STRIDX 129 
#define  MLX5_IB_CQE_RES_FORMAT_HASH 128 
 int /*<<< orphan*/  mini_cqe_resp_stride_index ; 

__attribute__((used)) static int mini_cqe_res_format_to_hw(struct mlx5_ib_dev *dev, u8 format)
{
	switch (format) {
	case MLX5_IB_CQE_RES_FORMAT_HASH:
		return MLX5_CQE_RES_FORMAT_HASH;
	case MLX5_IB_CQE_RES_FORMAT_CSUM:
		return MLX5_CQE_RES_FORMAT_CSUM;
	case MLX5_IB_CQE_RES_FORMAT_CSUM_STRIDX:
		if (MLX5_CAP_GEN(dev->mdev, mini_cqe_resp_stride_index))
			return MLX5_CQE_RES_FORMAT_CSUM_STRIDX;
		return -EOPNOTSUPP;
	default:
		return -EINVAL;
	}
}