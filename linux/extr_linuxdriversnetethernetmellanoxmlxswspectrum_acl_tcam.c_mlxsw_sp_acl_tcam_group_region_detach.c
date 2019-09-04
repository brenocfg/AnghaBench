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
struct mlxsw_sp_acl_tcam_region {struct mlxsw_sp_acl_tcam_group* group; } ;
struct mlxsw_sp_acl_tcam_group {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_group_list_del (struct mlxsw_sp_acl_tcam_group*,struct mlxsw_sp_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_group_update (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_group*) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_group_region_detach(struct mlxsw_sp *mlxsw_sp,
				      struct mlxsw_sp_acl_tcam_region *region)
{
	struct mlxsw_sp_acl_tcam_group *group = region->group;

	mlxsw_sp_acl_tcam_group_list_del(group, region);
	mlxsw_sp_acl_tcam_group_update(mlxsw_sp, group);
}