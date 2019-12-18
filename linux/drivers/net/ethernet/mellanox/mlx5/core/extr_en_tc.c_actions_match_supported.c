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
typedef  int u32 ;
struct netlink_ext_ack {int dummy; } ;
struct mlx5e_tc_flow_parse_attr {int /*<<< orphan*/  spec; } ;
struct mlx5e_tc_flow {TYPE_2__* nic_attr; TYPE_1__* esw_attr; } ;
struct mlx5e_priv {int dummy; } ;
struct flow_action {int dummy; } ;
struct TYPE_4__ {int action; } ;
struct TYPE_3__ {int action; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGRESS ; 
 int MLX5_FLOW_CONTEXT_ACTION_DECAP ; 
 int MLX5_FLOW_CONTEXT_ACTION_DROP ; 
 int MLX5_FLOW_CONTEXT_ACTION_MOD_HDR ; 
 int MLX5_FLOW_CONTEXT_ACTION_VLAN_POP ; 
 scalar_t__ flow_flag_test (struct mlx5e_tc_flow*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5e_is_eswitch_flow (struct mlx5e_tc_flow*) ; 
 int modify_header_match_supported (int /*<<< orphan*/ *,struct flow_action*,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static bool actions_match_supported(struct mlx5e_priv *priv,
				    struct flow_action *flow_action,
				    struct mlx5e_tc_flow_parse_attr *parse_attr,
				    struct mlx5e_tc_flow *flow,
				    struct netlink_ext_ack *extack)
{
	u32 actions;

	if (mlx5e_is_eswitch_flow(flow))
		actions = flow->esw_attr->action;
	else
		actions = flow->nic_attr->action;

	if (flow_flag_test(flow, EGRESS) &&
	    !((actions & MLX5_FLOW_CONTEXT_ACTION_DECAP) ||
	      (actions & MLX5_FLOW_CONTEXT_ACTION_VLAN_POP) ||
	      (actions & MLX5_FLOW_CONTEXT_ACTION_DROP)))
		return false;

	if (actions & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		return modify_header_match_supported(&parse_attr->spec,
						     flow_action, actions,
						     extack);

	return true;
}