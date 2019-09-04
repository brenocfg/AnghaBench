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
typedef  scalar_t__ u64 ;
struct uverbs_attr_bundle {int dummy; } ;
struct mlx5_ib_dm {scalar_t__ dev_addr; } ;
struct ib_pd {int dummy; } ;
struct ib_mr {int dummy; } ;
struct ib_dm_mr_attr {int access_flags; int /*<<< orphan*/  length; scalar_t__ offset; } ;
struct ib_dm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ib_mr* ERR_PTR (int /*<<< orphan*/ ) ; 
 int MLX5_IB_DM_ALLOWED_ACCESS ; 
 struct ib_mr* mlx5_ib_get_memic_mr (struct ib_pd*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct mlx5_ib_dm* to_mdm (struct ib_dm*) ; 

struct ib_mr *mlx5_ib_reg_dm_mr(struct ib_pd *pd, struct ib_dm *dm,
				struct ib_dm_mr_attr *attr,
				struct uverbs_attr_bundle *attrs)
{
	struct mlx5_ib_dm *mdm = to_mdm(dm);
	u64 memic_addr;

	if (attr->access_flags & ~MLX5_IB_DM_ALLOWED_ACCESS)
		return ERR_PTR(-EINVAL);

	memic_addr = mdm->dev_addr + attr->offset;

	return mlx5_ib_get_memic_mr(pd, memic_addr, attr->length,
				    attr->access_flags);
}