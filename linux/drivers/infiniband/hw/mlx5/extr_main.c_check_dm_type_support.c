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
typedef  int u32 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_RAW ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  MLX5_CAP_DEV_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_FLOWTABLE_NIC_RX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_FLOWTABLE_NIC_TX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  MLX5_IB_UAPI_DM_TYPE_HEADER_MODIFY_SW_ICM 130 
#define  MLX5_IB_UAPI_DM_TYPE_MEMIC 129 
#define  MLX5_IB_UAPI_DM_TYPE_STEERING_SW_ICM 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memic ; 
 int /*<<< orphan*/  sw_owner ; 

__attribute__((used)) static inline int check_dm_type_support(struct mlx5_ib_dev *dev,
					u32 type)
{
	switch (type) {
	case MLX5_IB_UAPI_DM_TYPE_MEMIC:
		if (!MLX5_CAP_DEV_MEM(dev->mdev, memic))
			return -EOPNOTSUPP;
		break;
	case MLX5_IB_UAPI_DM_TYPE_STEERING_SW_ICM:
	case MLX5_IB_UAPI_DM_TYPE_HEADER_MODIFY_SW_ICM:
		if (!capable(CAP_SYS_RAWIO) ||
		    !capable(CAP_NET_RAW))
			return -EPERM;

		if (!(MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev, sw_owner) ||
		      MLX5_CAP_FLOWTABLE_NIC_TX(dev->mdev, sw_owner)))
			return -EOPNOTSUPP;
		break;
	}

	return 0;
}