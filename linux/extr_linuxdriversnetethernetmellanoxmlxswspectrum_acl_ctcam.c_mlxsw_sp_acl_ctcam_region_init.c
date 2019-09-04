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
struct mlxsw_sp_acl_tcam_region {int dummy; } ;
struct mlxsw_sp_acl_ctcam_region_ops {int dummy; } ;
struct mlxsw_sp_acl_ctcam_region {int /*<<< orphan*/  parman; struct mlxsw_sp_acl_ctcam_region_ops const* ops; struct mlxsw_sp_acl_tcam_region* region; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ctcam_region_parman_ops ; 
 int /*<<< orphan*/  parman_create (int /*<<< orphan*/ *,struct mlxsw_sp_acl_ctcam_region*) ; 

int
mlxsw_sp_acl_ctcam_region_init(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_acl_ctcam_region *cregion,
			       struct mlxsw_sp_acl_tcam_region *region,
			       const struct mlxsw_sp_acl_ctcam_region_ops *ops)
{
	cregion->region = region;
	cregion->ops = ops;
	cregion->parman = parman_create(&mlxsw_sp_acl_ctcam_region_parman_ops,
					cregion);
	if (!cregion->parman)
		return -ENOMEM;
	return 0;
}