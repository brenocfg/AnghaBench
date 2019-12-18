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
struct mlxsw_sp_acl_ruleset {int dummy; } ;
struct mlxsw_sp_acl_rule {int dummy; } ;
struct mlxsw_sp_acl_block {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chain_index; } ;
struct flow_cls_offload {int /*<<< orphan*/  cookie; TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_ruleset*) ; 
 int /*<<< orphan*/  MLXSW_SP_ACL_PROFILE_FLOWER ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rule_del (struct mlxsw_sp*,struct mlxsw_sp_acl_rule*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rule_destroy (struct mlxsw_sp*,struct mlxsw_sp_acl_rule*) ; 
 struct mlxsw_sp_acl_rule* mlxsw_sp_acl_rule_lookup (struct mlxsw_sp*,struct mlxsw_sp_acl_ruleset*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_acl_ruleset* mlxsw_sp_acl_ruleset_get (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ruleset_put (struct mlxsw_sp*,struct mlxsw_sp_acl_ruleset*) ; 

void mlxsw_sp_flower_destroy(struct mlxsw_sp *mlxsw_sp,
			     struct mlxsw_sp_acl_block *block,
			     struct flow_cls_offload *f)
{
	struct mlxsw_sp_acl_ruleset *ruleset;
	struct mlxsw_sp_acl_rule *rule;

	ruleset = mlxsw_sp_acl_ruleset_get(mlxsw_sp, block,
					   f->common.chain_index,
					   MLXSW_SP_ACL_PROFILE_FLOWER, NULL);
	if (IS_ERR(ruleset))
		return;

	rule = mlxsw_sp_acl_rule_lookup(mlxsw_sp, ruleset, f->cookie);
	if (rule) {
		mlxsw_sp_acl_rule_del(mlxsw_sp, rule);
		mlxsw_sp_acl_rule_destroy(mlxsw_sp, rule);
	}

	mlxsw_sp_acl_ruleset_put(mlxsw_sp, ruleset);
}