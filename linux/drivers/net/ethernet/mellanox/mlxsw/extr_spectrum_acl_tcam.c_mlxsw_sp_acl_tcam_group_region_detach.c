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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  list; struct mlxsw_sp_acl_tcam_group* group; } ;
struct mlxsw_sp_acl_tcam_group {int /*<<< orphan*/  lock; int /*<<< orphan*/  region_count; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_group_update (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_group*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_group_region_detach(struct mlxsw_sp *mlxsw_sp,
				      struct mlxsw_sp_acl_tcam_region *region)
{
	struct mlxsw_sp_acl_tcam_group *group = region->group;

	mutex_lock(&group->lock);
	list_del(&region->list);
	group->region_count--;
	mlxsw_sp_acl_tcam_group_update(mlxsw_sp, group);
	mutex_unlock(&group->lock);
}