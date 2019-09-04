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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct mlxsw_sp_acl_profile_ops const* ops; int /*<<< orphan*/  chain_index; struct mlxsw_sp_acl_block* block; } ;
struct mlxsw_sp_acl_ruleset {int ref_count; int /*<<< orphan*/  rule_ht; int /*<<< orphan*/  priv; int /*<<< orphan*/  ht_node; TYPE_1__ ht_key; } ;
struct mlxsw_sp_acl_profile_ops {int ruleset_priv_size; int (* ruleset_add ) (struct mlxsw_sp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlxsw_afk_element_usage*) ;int /*<<< orphan*/  (* ruleset_del ) (struct mlxsw_sp*,int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp_acl_block {int dummy; } ;
struct mlxsw_sp_acl {int /*<<< orphan*/  ruleset_ht; int /*<<< orphan*/  tcam; } ;
struct mlxsw_sp {struct mlxsw_sp_acl* acl; } ;
struct mlxsw_afk_element_usage {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_acl_ruleset* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_ruleset*) ; 
 struct mlxsw_sp_acl_ruleset* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rule_ht_params ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ruleset_ht_params ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlxsw_afk_element_usage*) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_acl_ruleset *
mlxsw_sp_acl_ruleset_create(struct mlxsw_sp *mlxsw_sp,
			    struct mlxsw_sp_acl_block *block, u32 chain_index,
			    const struct mlxsw_sp_acl_profile_ops *ops,
			    struct mlxsw_afk_element_usage *tmplt_elusage)
{
	struct mlxsw_sp_acl *acl = mlxsw_sp->acl;
	struct mlxsw_sp_acl_ruleset *ruleset;
	size_t alloc_size;
	int err;

	alloc_size = sizeof(*ruleset) + ops->ruleset_priv_size;
	ruleset = kzalloc(alloc_size, GFP_KERNEL);
	if (!ruleset)
		return ERR_PTR(-ENOMEM);
	ruleset->ref_count = 1;
	ruleset->ht_key.block = block;
	ruleset->ht_key.chain_index = chain_index;
	ruleset->ht_key.ops = ops;

	err = rhashtable_init(&ruleset->rule_ht, &mlxsw_sp_acl_rule_ht_params);
	if (err)
		goto err_rhashtable_init;

	err = ops->ruleset_add(mlxsw_sp, &acl->tcam, ruleset->priv,
			       tmplt_elusage);
	if (err)
		goto err_ops_ruleset_add;

	err = rhashtable_insert_fast(&acl->ruleset_ht, &ruleset->ht_node,
				     mlxsw_sp_acl_ruleset_ht_params);
	if (err)
		goto err_ht_insert;

	return ruleset;

err_ht_insert:
	ops->ruleset_del(mlxsw_sp, ruleset->priv);
err_ops_ruleset_add:
	rhashtable_destroy(&ruleset->rule_ht);
err_rhashtable_init:
	kfree(ruleset);
	return ERR_PTR(err);
}