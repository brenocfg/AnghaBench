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
struct tcf_exts {int dummy; } ;
struct mlx5e_tc_flow_parse_attr {int /*<<< orphan*/  spec; } ;
struct mlx5e_tc_flow {int flags; TYPE_2__* nic_attr; TYPE_1__* esw_attr; } ;
struct mlx5e_priv {int dummy; } ;
struct TYPE_4__ {int action; } ;
struct TYPE_3__ {int action; } ;

/* Variables and functions */
 int MLX5E_TC_FLOW_EGRESS ; 
 int MLX5E_TC_FLOW_ESWITCH ; 
 int MLX5_FLOW_CONTEXT_ACTION_DECAP ; 
 int MLX5_FLOW_CONTEXT_ACTION_MOD_HDR ; 
 int modify_header_match_supported (int /*<<< orphan*/ *,struct tcf_exts*) ; 

__attribute__((used)) static bool actions_match_supported(struct mlx5e_priv *priv,
				    struct tcf_exts *exts,
				    struct mlx5e_tc_flow_parse_attr *parse_attr,
				    struct mlx5e_tc_flow *flow)
{
	u32 actions;

	if (flow->flags & MLX5E_TC_FLOW_ESWITCH)
		actions = flow->esw_attr->action;
	else
		actions = flow->nic_attr->action;

	if (flow->flags & MLX5E_TC_FLOW_EGRESS &&
	    !(actions & MLX5_FLOW_CONTEXT_ACTION_DECAP))
		return false;

	if (actions & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		return modify_header_match_supported(&parse_attr->spec, exts);

	return true;
}