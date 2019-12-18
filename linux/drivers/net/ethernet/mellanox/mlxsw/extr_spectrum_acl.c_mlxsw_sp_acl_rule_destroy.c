#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlxsw_sp_acl_ruleset {int dummy; } ;
struct mlxsw_sp_acl_rule {int /*<<< orphan*/  rulei; struct mlxsw_sp_acl_ruleset* ruleset; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_rule*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rulei_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ruleset_ref_dec (struct mlxsw_sp*,struct mlxsw_sp_acl_ruleset*) ; 

void mlxsw_sp_acl_rule_destroy(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_acl_rule *rule)
{
	struct mlxsw_sp_acl_ruleset *ruleset = rule->ruleset;

	mlxsw_sp_acl_rulei_destroy(rule->rulei);
	kfree(rule);
	mlxsw_sp_acl_ruleset_ref_dec(mlxsw_sp, ruleset);
}