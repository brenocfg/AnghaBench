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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  priv; } ;
struct mlxsw_sp_acl_tcam_ops {int (* entry_action_replace ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_acl_rule_info*) ;} ;
struct mlxsw_sp_acl_tcam_entry {int /*<<< orphan*/  priv; } ;
struct mlxsw_sp_acl_rule_info {int dummy; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;

/* Variables and functions */
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_acl_rule_info*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_entry_action_replace(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_acl_tcam_region *region,
				       struct mlxsw_sp_acl_tcam_entry *entry,
				       struct mlxsw_sp_acl_rule_info *rulei)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	return ops->entry_action_replace(mlxsw_sp, region->priv,
					 entry->priv, rulei);
}