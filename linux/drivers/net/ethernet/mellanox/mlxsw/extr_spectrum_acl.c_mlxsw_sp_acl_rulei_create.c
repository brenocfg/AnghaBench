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
struct mlxsw_sp_acl_rule_info {int action_created; struct mlxsw_afa_block* act_block; } ;
struct mlxsw_sp_acl {TYPE_1__* mlxsw_sp; } ;
struct mlxsw_afa_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  afa; } ;

/* Variables and functions */
 struct mlxsw_sp_acl_rule_info* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mlxsw_afa_block*) ; 
 int PTR_ERR (struct mlxsw_afa_block*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_rule_info*) ; 
 struct mlxsw_sp_acl_rule_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct mlxsw_afa_block* mlxsw_afa_block_create (int /*<<< orphan*/ ) ; 

struct mlxsw_sp_acl_rule_info *
mlxsw_sp_acl_rulei_create(struct mlxsw_sp_acl *acl,
			  struct mlxsw_afa_block *afa_block)
{
	struct mlxsw_sp_acl_rule_info *rulei;
	int err;

	rulei = kzalloc(sizeof(*rulei), GFP_KERNEL);
	if (!rulei)
		return NULL;

	if (afa_block) {
		rulei->act_block = afa_block;
		return rulei;
	}

	rulei->act_block = mlxsw_afa_block_create(acl->mlxsw_sp->afa);
	if (IS_ERR(rulei->act_block)) {
		err = PTR_ERR(rulei->act_block);
		goto err_afa_block_create;
	}
	rulei->action_created = 1;
	return rulei;

err_afa_block_create:
	kfree(rulei);
	return ERR_PTR(err);
}