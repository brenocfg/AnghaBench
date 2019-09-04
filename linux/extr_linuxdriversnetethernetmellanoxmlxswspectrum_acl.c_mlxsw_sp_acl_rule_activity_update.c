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
struct mlxsw_sp_acl_rule {int /*<<< orphan*/  last_used; int /*<<< orphan*/  priv; struct mlxsw_sp_acl_ruleset* ruleset; } ;
struct mlxsw_sp_acl_profile_ops {int (* rule_activity_get ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int*) ;} ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mlxsw_sp_acl_rule_activity_update(struct mlxsw_sp *mlxsw_sp,
					     struct mlxsw_sp_acl_rule *rule)
{
	struct mlxsw_sp_acl_ruleset *ruleset = rule->ruleset;
	const struct mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;
	bool active;
	int err;

	err = ops->rule_activity_get(mlxsw_sp, rule->priv, &active);
	if (err)
		return err;
	if (active)
		rule->last_used = jiffies;
	return 0;
}