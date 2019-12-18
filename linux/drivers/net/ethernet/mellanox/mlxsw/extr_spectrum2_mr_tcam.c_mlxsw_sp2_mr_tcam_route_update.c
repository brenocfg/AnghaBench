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
struct mlxsw_sp_mr_route_key {int /*<<< orphan*/  proto; } ;
struct mlxsw_sp_acl_ruleset {int dummy; } ;
struct mlxsw_sp_acl_rule {int dummy; } ;
struct mlxsw_sp2_mr_tcam {int dummy; } ;
struct mlxsw_sp2_mr_route {struct mlxsw_sp2_mr_tcam* mr_tcam; } ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_afa_block {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 struct mlxsw_sp_acl_ruleset* mlxsw_sp2_mr_tcam_proto_ruleset (struct mlxsw_sp2_mr_tcam*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_acl_rule_action_replace (struct mlxsw_sp*,struct mlxsw_sp_acl_rule*,struct mlxsw_afa_block*) ; 
 struct mlxsw_sp_acl_rule* mlxsw_sp_acl_rule_lookup (struct mlxsw_sp*,struct mlxsw_sp_acl_ruleset*,unsigned long) ; 

__attribute__((used)) static int
mlxsw_sp2_mr_tcam_route_update(struct mlxsw_sp *mlxsw_sp,
			       void *route_priv,
			       struct mlxsw_sp_mr_route_key *key,
			       struct mlxsw_afa_block *afa_block)
{
	struct mlxsw_sp2_mr_route *mr_route = route_priv;
	struct mlxsw_sp2_mr_tcam *mr_tcam = mr_route->mr_tcam;
	struct mlxsw_sp_acl_ruleset *ruleset;
	struct mlxsw_sp_acl_rule *rule;

	ruleset = mlxsw_sp2_mr_tcam_proto_ruleset(mr_tcam, key->proto);
	if (WARN_ON(!ruleset))
		return -EINVAL;

	rule = mlxsw_sp_acl_rule_lookup(mlxsw_sp, ruleset,
					(unsigned long) route_priv);
	if (WARN_ON(!rule))
		return -EINVAL;

	return mlxsw_sp_acl_rule_action_replace(mlxsw_sp, rule, afa_block);
}