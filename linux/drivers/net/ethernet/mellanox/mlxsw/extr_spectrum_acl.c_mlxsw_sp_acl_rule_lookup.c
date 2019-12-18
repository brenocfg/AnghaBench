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
struct mlxsw_sp_acl_ruleset {int /*<<< orphan*/  rule_ht; } ;
struct mlxsw_sp_acl_rule {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_rule_ht_params ; 
 struct mlxsw_sp_acl_rule* rhashtable_lookup_fast (int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ ) ; 

struct mlxsw_sp_acl_rule *
mlxsw_sp_acl_rule_lookup(struct mlxsw_sp *mlxsw_sp,
			 struct mlxsw_sp_acl_ruleset *ruleset,
			 unsigned long cookie)
{
	return rhashtable_lookup_fast(&ruleset->rule_ht, &cookie,
				       mlxsw_sp_acl_rule_ht_params);
}