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
struct mlxsw_sp_acl_tcam_flower_ruleset {int /*<<< orphan*/  vgroup; } ;
struct mlxsw_sp_acl_tcam_flower_rule {int /*<<< orphan*/  ventry; } ;
struct mlxsw_sp_acl_rule_info {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_acl_tcam_ventry_add (struct mlxsw_sp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mlxsw_sp_acl_rule_info*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_flower_rule_add(struct mlxsw_sp *mlxsw_sp,
				  void *ruleset_priv, void *rule_priv,
				  struct mlxsw_sp_acl_rule_info *rulei)
{
	struct mlxsw_sp_acl_tcam_flower_ruleset *ruleset = ruleset_priv;
	struct mlxsw_sp_acl_tcam_flower_rule *rule = rule_priv;

	return mlxsw_sp_acl_tcam_ventry_add(mlxsw_sp, &ruleset->vgroup,
					    &rule->ventry, rulei);
}