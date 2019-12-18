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
struct mlxsw_sp_acl_rule_info {int dummy; } ;
typedef  struct mlxsw_sp_acl_ruleset mlxsw_sp_acl_rule ;
struct mlxsw_sp_acl_block {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  extack; int /*<<< orphan*/  chain_index; } ;
struct flow_cls_offload {TYPE_1__ common; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_ruleset*) ; 
 int /*<<< orphan*/  MLXSW_SP_ACL_PROFILE_FLOWER ; 
 int PTR_ERR (struct mlxsw_sp_acl_ruleset*) ; 
 int mlxsw_sp_acl_rule_add (struct mlxsw_sp*,struct mlxsw_sp_acl_ruleset*) ; 
 struct mlxsw_sp_acl_ruleset* mlxsw_sp_acl_rule_create (struct mlxsw_sp*,struct mlxsw_sp_acl_ruleset*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rule_destroy (struct mlxsw_sp*,struct mlxsw_sp_acl_ruleset*) ; 
 struct mlxsw_sp_acl_rule_info* mlxsw_sp_acl_rule_rulei (struct mlxsw_sp_acl_ruleset*) ; 
 int mlxsw_sp_acl_rulei_commit (struct mlxsw_sp_acl_rule_info*) ; 
 struct mlxsw_sp_acl_ruleset* mlxsw_sp_acl_ruleset_get (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ruleset_put (struct mlxsw_sp*,struct mlxsw_sp_acl_ruleset*) ; 
 int mlxsw_sp_flower_parse (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct mlxsw_sp_acl_rule_info*,struct flow_cls_offload*) ; 

int mlxsw_sp_flower_replace(struct mlxsw_sp *mlxsw_sp,
			    struct mlxsw_sp_acl_block *block,
			    struct flow_cls_offload *f)
{
	struct mlxsw_sp_acl_rule_info *rulei;
	struct mlxsw_sp_acl_ruleset *ruleset;
	struct mlxsw_sp_acl_rule *rule;
	int err;

	ruleset = mlxsw_sp_acl_ruleset_get(mlxsw_sp, block,
					   f->common.chain_index,
					   MLXSW_SP_ACL_PROFILE_FLOWER, NULL);
	if (IS_ERR(ruleset))
		return PTR_ERR(ruleset);

	rule = mlxsw_sp_acl_rule_create(mlxsw_sp, ruleset, f->cookie, NULL,
					f->common.extack);
	if (IS_ERR(rule)) {
		err = PTR_ERR(rule);
		goto err_rule_create;
	}

	rulei = mlxsw_sp_acl_rule_rulei(rule);
	err = mlxsw_sp_flower_parse(mlxsw_sp, block, rulei, f);
	if (err)
		goto err_flower_parse;

	err = mlxsw_sp_acl_rulei_commit(rulei);
	if (err)
		goto err_rulei_commit;

	err = mlxsw_sp_acl_rule_add(mlxsw_sp, rule);
	if (err)
		goto err_rule_add;

	mlxsw_sp_acl_ruleset_put(mlxsw_sp, ruleset);
	return 0;

err_rule_add:
err_rulei_commit:
err_flower_parse:
	mlxsw_sp_acl_rule_destroy(mlxsw_sp, rule);
err_rule_create:
	mlxsw_sp_acl_ruleset_put(mlxsw_sp, ruleset);
	return err;
}