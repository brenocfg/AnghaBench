#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  chain_index; struct mlxsw_sp_acl_block* block; struct mlxsw_sp_acl_profile_ops* ops; } ;
struct mlxsw_sp_acl_ruleset {int /*<<< orphan*/  rule_ht; TYPE_1__ ht_key; int /*<<< orphan*/  priv; } ;
struct mlxsw_sp_acl_rule {int /*<<< orphan*/  priv; int /*<<< orphan*/  ht_node; TYPE_3__* rulei; int /*<<< orphan*/  list; struct mlxsw_sp_acl_ruleset* ruleset; } ;
struct mlxsw_sp_acl_profile_ops {int (* rule_add ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ;int /*<<< orphan*/  (* rule_del ) (struct mlxsw_sp*,int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp_acl_block {int /*<<< orphan*/  egress_blocker_rule_count; int /*<<< orphan*/  rule_count; } ;
struct mlxsw_sp {TYPE_2__* acl; } ;
struct TYPE_6__ {scalar_t__ egress_bind_blocker; } ;
struct TYPE_5__ {int /*<<< orphan*/  rules; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rule_ht_params ; 
 int mlxsw_sp_acl_ruleset_block_bind (struct mlxsw_sp*,struct mlxsw_sp_acl_ruleset*,struct mlxsw_sp_acl_block*) ; 
 scalar_t__ mlxsw_sp_acl_ruleset_is_singular (struct mlxsw_sp_acl_ruleset*) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

int mlxsw_sp_acl_rule_add(struct mlxsw_sp *mlxsw_sp,
			  struct mlxsw_sp_acl_rule *rule)
{
	struct mlxsw_sp_acl_ruleset *ruleset = rule->ruleset;
	const struct mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;
	struct mlxsw_sp_acl_block *block = ruleset->ht_key.block;
	int err;

	err = ops->rule_add(mlxsw_sp, ruleset->priv, rule->priv, rule->rulei);
	if (err)
		return err;

	err = rhashtable_insert_fast(&ruleset->rule_ht, &rule->ht_node,
				     mlxsw_sp_acl_rule_ht_params);
	if (err)
		goto err_rhashtable_insert;

	if (!ruleset->ht_key.chain_index &&
	    mlxsw_sp_acl_ruleset_is_singular(ruleset)) {
		/* We only need ruleset with chain index 0, the implicit
		 * one, to be directly bound to device. The rest of the
		 * rulesets are bound by "Goto action set".
		 */
		err = mlxsw_sp_acl_ruleset_block_bind(mlxsw_sp, ruleset, block);
		if (err)
			goto err_ruleset_block_bind;
	}

	list_add_tail(&rule->list, &mlxsw_sp->acl->rules);
	block->rule_count++;
	block->egress_blocker_rule_count += rule->rulei->egress_bind_blocker;
	return 0;

err_ruleset_block_bind:
	rhashtable_remove_fast(&ruleset->rule_ht, &rule->ht_node,
			       mlxsw_sp_acl_rule_ht_params);
err_rhashtable_insert:
	ops->rule_del(mlxsw_sp, rule->priv);
	return err;
}