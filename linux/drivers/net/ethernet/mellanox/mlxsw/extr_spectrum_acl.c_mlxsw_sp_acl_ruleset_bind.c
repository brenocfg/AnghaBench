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
struct mlxsw_sp_acl_ruleset {int /*<<< orphan*/  priv; TYPE_1__ ht_key; } ;
struct mlxsw_sp_acl_profile_ops {int (* ruleset_bind ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp_acl_block_binding {int /*<<< orphan*/  ingress; int /*<<< orphan*/  mlxsw_sp_port; } ;
struct mlxsw_sp_acl_block {struct mlxsw_sp_acl_ruleset* ruleset_zero; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_acl_ruleset_bind(struct mlxsw_sp *mlxsw_sp,
			  struct mlxsw_sp_acl_block *block,
			  struct mlxsw_sp_acl_block_binding *binding)
{
	struct mlxsw_sp_acl_ruleset *ruleset = block->ruleset_zero;
	const struct mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;

	return ops->ruleset_bind(mlxsw_sp, ruleset->priv,
				 binding->mlxsw_sp_port, binding->ingress);
}