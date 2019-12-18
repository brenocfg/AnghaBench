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
struct mlx5e_tc_flow {struct mlx5_flow_handle** rule; } ;
struct mlx5_flow_spec {int dummy; } ;
struct mlx5_flow_handle {int dummy; } ;
struct mlx5_eswitch {int dummy; } ;
struct mlx5_esw_flow_attr {scalar_t__ split_count; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx5_flow_handle*) ; 
 struct mlx5_flow_handle* mlx5_eswitch_add_fwd_rule (struct mlx5_eswitch*,struct mlx5_flow_spec*,struct mlx5_esw_flow_attr*) ; 
 struct mlx5_flow_handle* mlx5_eswitch_add_offloaded_rule (struct mlx5_eswitch*,struct mlx5_flow_spec*,struct mlx5_esw_flow_attr*) ; 
 int /*<<< orphan*/  mlx5_eswitch_del_offloaded_rule (struct mlx5_eswitch*,struct mlx5_flow_handle*,struct mlx5_esw_flow_attr*) ; 

__attribute__((used)) static struct mlx5_flow_handle *
mlx5e_tc_offload_fdb_rules(struct mlx5_eswitch *esw,
			   struct mlx5e_tc_flow *flow,
			   struct mlx5_flow_spec *spec,
			   struct mlx5_esw_flow_attr *attr)
{
	struct mlx5_flow_handle *rule;

	rule = mlx5_eswitch_add_offloaded_rule(esw, spec, attr);
	if (IS_ERR(rule))
		return rule;

	if (attr->split_count) {
		flow->rule[1] = mlx5_eswitch_add_fwd_rule(esw, spec, attr);
		if (IS_ERR(flow->rule[1])) {
			mlx5_eswitch_del_offloaded_rule(esw, rule, attr);
			return flow->rule[1];
		}
	}

	return rule;
}