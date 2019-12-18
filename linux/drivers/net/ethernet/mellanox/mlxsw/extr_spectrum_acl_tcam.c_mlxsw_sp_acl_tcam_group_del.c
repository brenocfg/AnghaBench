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
struct mlxsw_sp_acl_tcam_group {int /*<<< orphan*/  region_list; int /*<<< orphan*/  id; int /*<<< orphan*/  lock; struct mlxsw_sp_acl_tcam* tcam; } ;
struct mlxsw_sp_acl_tcam {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_group_id_put (struct mlxsw_sp_acl_tcam*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_acl_tcam_group_del(struct mlxsw_sp_acl_tcam_group *group)
{
	struct mlxsw_sp_acl_tcam *tcam = group->tcam;

	mutex_destroy(&group->lock);
	mlxsw_sp_acl_tcam_group_id_put(tcam, group->id);
	WARN_ON(!list_empty(&group->region_list));
}