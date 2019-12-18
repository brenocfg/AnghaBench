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
struct mlxsw_sp_acl_tcam_ops {int /*<<< orphan*/  region_rehash_hints_get; } ;
struct mlxsw_sp_acl_tcam {int /*<<< orphan*/  vregion_rehash_intrvl; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 

u32 mlxsw_sp_acl_tcam_vregion_rehash_intrvl_get(struct mlxsw_sp *mlxsw_sp,
						struct mlxsw_sp_acl_tcam *tcam)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	u32 vregion_rehash_intrvl;

	if (WARN_ON(!ops->region_rehash_hints_get))
		return 0;
	vregion_rehash_intrvl = tcam->vregion_rehash_intrvl;
	return vregion_rehash_intrvl;
}