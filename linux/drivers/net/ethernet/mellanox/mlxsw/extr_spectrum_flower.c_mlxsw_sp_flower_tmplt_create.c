#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_acl_ruleset {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  elusage; } ;
struct mlxsw_sp_acl_rule_info {TYPE_2__ values; } ;
struct mlxsw_sp_acl_block {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  chain_index; } ;
struct flow_cls_offload {TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  rulei ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_ACL_PROFILE_FLOWER ; 
 int PTR_ERR_OR_ZERO (struct mlxsw_sp_acl_ruleset*) ; 
 int /*<<< orphan*/  memset (struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ ,int) ; 
 struct mlxsw_sp_acl_ruleset* mlxsw_sp_acl_ruleset_get (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_flower_parse (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct mlxsw_sp_acl_rule_info*,struct flow_cls_offload*) ; 

int mlxsw_sp_flower_tmplt_create(struct mlxsw_sp *mlxsw_sp,
				 struct mlxsw_sp_acl_block *block,
				 struct flow_cls_offload *f)
{
	struct mlxsw_sp_acl_ruleset *ruleset;
	struct mlxsw_sp_acl_rule_info rulei;
	int err;

	memset(&rulei, 0, sizeof(rulei));
	err = mlxsw_sp_flower_parse(mlxsw_sp, block, &rulei, f);
	if (err)
		return err;
	ruleset = mlxsw_sp_acl_ruleset_get(mlxsw_sp, block,
					   f->common.chain_index,
					   MLXSW_SP_ACL_PROFILE_FLOWER,
					   &rulei.values.elusage);

	/* keep the reference to the ruleset */
	return PTR_ERR_OR_ZERO(ruleset);
}