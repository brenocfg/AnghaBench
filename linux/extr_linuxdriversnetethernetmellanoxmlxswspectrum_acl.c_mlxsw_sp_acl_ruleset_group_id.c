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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {struct mlxsw_sp_acl_profile_ops* ops; } ;
struct mlxsw_sp_acl_ruleset {int /*<<< orphan*/  priv; TYPE_1__ ht_key; } ;
struct mlxsw_sp_acl_profile_ops {int /*<<< orphan*/  (* ruleset_group_id ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

u16 mlxsw_sp_acl_ruleset_group_id(struct mlxsw_sp_acl_ruleset *ruleset)
{
	const struct mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;

	return ops->ruleset_group_id(ruleset->priv);
}