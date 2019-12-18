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
struct TYPE_2__ {struct mlxsw_sp_acl_profile_ops* ops; } ;
struct mlxsw_sp_acl_ruleset {TYPE_1__ ht_key; } ;
struct mlxsw_sp_acl_rule_info {struct mlxsw_afa_block* act_block; } ;
struct mlxsw_sp_acl_rule {int /*<<< orphan*/  rulei; int /*<<< orphan*/  priv; struct mlxsw_sp_acl_ruleset* ruleset; } ;
struct mlxsw_sp_acl_profile_ops {int (* rule_action_replace ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_afa_block {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_acl_rule_info* mlxsw_sp_acl_rule_rulei (struct mlxsw_sp_acl_rule*) ; 
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlxsw_sp_acl_rule_action_replace(struct mlxsw_sp *mlxsw_sp,
				     struct mlxsw_sp_acl_rule *rule,
				     struct mlxsw_afa_block *afa_block)
{
	struct mlxsw_sp_acl_ruleset *ruleset = rule->ruleset;
	const struct mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;
	struct mlxsw_sp_acl_rule_info *rulei;

	rulei = mlxsw_sp_acl_rule_rulei(rule);
	rulei->act_block = afa_block;

	return ops->rule_action_replace(mlxsw_sp, rule->priv, rule->rulei);
}