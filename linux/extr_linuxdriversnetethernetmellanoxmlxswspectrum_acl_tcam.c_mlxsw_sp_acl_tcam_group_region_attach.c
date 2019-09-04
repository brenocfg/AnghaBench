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
struct mlxsw_sp_acl_tcam_region {struct mlxsw_sp_acl_tcam_group* group; } ;
struct mlxsw_sp_acl_tcam_group {scalar_t__ region_count; TYPE_1__* tcam; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_group_size; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_group_list_add (struct mlxsw_sp_acl_tcam_group*,struct mlxsw_sp_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_group_list_del (struct mlxsw_sp_acl_tcam_group*,struct mlxsw_sp_acl_tcam_region*) ; 
 int mlxsw_sp_acl_tcam_group_update (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_group*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_group_region_attach(struct mlxsw_sp *mlxsw_sp,
				      struct mlxsw_sp_acl_tcam_group *group,
				      struct mlxsw_sp_acl_tcam_region *region)
{
	int err;

	if (group->region_count == group->tcam->max_group_size)
		return -ENOBUFS;

	mlxsw_sp_acl_tcam_group_list_add(group, region);

	err = mlxsw_sp_acl_tcam_group_update(mlxsw_sp, group);
	if (err)
		goto err_group_update;
	region->group = group;

	return 0;

err_group_update:
	mlxsw_sp_acl_tcam_group_list_del(group, region);
	mlxsw_sp_acl_tcam_group_update(mlxsw_sp, group);
	return err;
}