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
typedef  scalar_t__ u64 ;
struct uverbs_attr_bundle {int dummy; } ;
struct mlx5_ib_dm {int type; scalar_t__ dev_addr; } ;
struct mlx5_core_dev {int /*<<< orphan*/  pdev; } ;
struct ib_pd {int dummy; } ;
struct ib_mr {int dummy; } ;
struct ib_dm_mr_attr {int access_flags; int /*<<< orphan*/  length; scalar_t__ offset; } ;
struct ib_dm {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {struct mlx5_core_dev* mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ib_mr* ERR_PTR (int /*<<< orphan*/ ) ; 
 int MLX5_IB_DM_MEMIC_ALLOWED_ACCESS ; 
 int MLX5_IB_DM_SW_ICM_ALLOWED_ACCESS ; 
#define  MLX5_IB_UAPI_DM_TYPE_HEADER_MODIFY_SW_ICM 130 
#define  MLX5_IB_UAPI_DM_TYPE_MEMIC 129 
#define  MLX5_IB_UAPI_DM_TYPE_STEERING_SW_ICM 128 
 int MLX5_MKC_ACCESS_MODE_MEMIC ; 
 int MLX5_MKC_ACCESS_MODE_SW_ICM ; 
 struct ib_mr* mlx5_ib_get_dm_mr (struct ib_pd*,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dm* to_mdm (struct ib_dm*) ; 

struct ib_mr *mlx5_ib_reg_dm_mr(struct ib_pd *pd, struct ib_dm *dm,
				struct ib_dm_mr_attr *attr,
				struct uverbs_attr_bundle *attrs)
{
	struct mlx5_ib_dm *mdm = to_mdm(dm);
	struct mlx5_core_dev *dev = to_mdev(dm->device)->mdev;
	u64 start_addr = mdm->dev_addr + attr->offset;
	int mode;

	switch (mdm->type) {
	case MLX5_IB_UAPI_DM_TYPE_MEMIC:
		if (attr->access_flags & ~MLX5_IB_DM_MEMIC_ALLOWED_ACCESS)
			return ERR_PTR(-EINVAL);

		mode = MLX5_MKC_ACCESS_MODE_MEMIC;
		start_addr -= pci_resource_start(dev->pdev, 0);
		break;
	case MLX5_IB_UAPI_DM_TYPE_STEERING_SW_ICM:
	case MLX5_IB_UAPI_DM_TYPE_HEADER_MODIFY_SW_ICM:
		if (attr->access_flags & ~MLX5_IB_DM_SW_ICM_ALLOWED_ACCESS)
			return ERR_PTR(-EINVAL);

		mode = MLX5_MKC_ACCESS_MODE_SW_ICM;
		break;
	default:
		return ERR_PTR(-EINVAL);
	}

	return mlx5_ib_get_dm_mr(pd, start_addr, attr->length,
				 attr->access_flags, mode);
}