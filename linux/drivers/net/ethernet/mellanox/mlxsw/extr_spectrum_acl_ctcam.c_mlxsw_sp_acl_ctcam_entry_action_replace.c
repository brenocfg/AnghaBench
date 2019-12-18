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
struct mlxsw_sp_acl_rule_info {int /*<<< orphan*/  priority; int /*<<< orphan*/  act_block; } ;
struct mlxsw_sp_acl_ctcam_region {int dummy; } ;
struct mlxsw_sp_acl_ctcam_entry {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_acl_ctcam_region_entry_action_replace (struct mlxsw_sp*,struct mlxsw_sp_acl_ctcam_region*,struct mlxsw_sp_acl_ctcam_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlxsw_sp_acl_ctcam_entry_action_replace(struct mlxsw_sp *mlxsw_sp,
					    struct mlxsw_sp_acl_ctcam_region *cregion,
					    struct mlxsw_sp_acl_ctcam_entry *centry,
					    struct mlxsw_sp_acl_rule_info *rulei)
{
	return mlxsw_sp_acl_ctcam_region_entry_action_replace(mlxsw_sp, cregion,
							      centry,
							      rulei->act_block,
							      rulei->priority);
}