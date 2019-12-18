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
struct mlxsw_sp_acl_tcam_group {int /*<<< orphan*/  id; int /*<<< orphan*/  region_list; int /*<<< orphan*/  lock; struct mlxsw_sp_acl_tcam* tcam; } ;
struct mlxsw_sp_acl_tcam {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int mlxsw_sp_acl_tcam_group_id_get (struct mlxsw_sp_acl_tcam*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_group_add(struct mlxsw_sp_acl_tcam *tcam,
			    struct mlxsw_sp_acl_tcam_group *group)
{
	int err;

	group->tcam = tcam;
	mutex_init(&group->lock);
	INIT_LIST_HEAD(&group->region_list);

	err = mlxsw_sp_acl_tcam_group_id_get(tcam, &group->id);
	if (err)
		return err;

	return 0;
}