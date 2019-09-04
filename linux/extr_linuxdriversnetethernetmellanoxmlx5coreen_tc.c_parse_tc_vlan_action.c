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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tc_action {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct mlx5_esw_flow_attr {int total_vlan; scalar_t__* vlan_proto; scalar_t__* vlan_prio; int /*<<< orphan*/ * vlan_vid; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_VLAN_POP ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_VLAN_POP_2 ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2 ; 
 int MLX5_FS_VLAN_DEPTH ; 
 scalar_t__ TCA_VLAN_ACT_POP ; 
 scalar_t__ TCA_VLAN_ACT_PUSH ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_eswitch_vlan_actions_supported (int /*<<< orphan*/ ,int) ; 
 scalar_t__ tcf_vlan_action (struct tc_action const*) ; 
 scalar_t__ tcf_vlan_push_prio (struct tc_action const*) ; 
 scalar_t__ tcf_vlan_push_proto (struct tc_action const*) ; 
 int /*<<< orphan*/  tcf_vlan_push_vid (struct tc_action const*) ; 

__attribute__((used)) static int parse_tc_vlan_action(struct mlx5e_priv *priv,
				const struct tc_action *a,
				struct mlx5_esw_flow_attr *attr,
				u32 *action)
{
	u8 vlan_idx = attr->total_vlan;

	if (vlan_idx >= MLX5_FS_VLAN_DEPTH)
		return -EOPNOTSUPP;

	if (tcf_vlan_action(a) == TCA_VLAN_ACT_POP) {
		if (vlan_idx) {
			if (!mlx5_eswitch_vlan_actions_supported(priv->mdev,
								 MLX5_FS_VLAN_DEPTH))
				return -EOPNOTSUPP;

			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_POP_2;
		} else {
			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_POP;
		}
	} else if (tcf_vlan_action(a) == TCA_VLAN_ACT_PUSH) {
		attr->vlan_vid[vlan_idx] = tcf_vlan_push_vid(a);
		attr->vlan_prio[vlan_idx] = tcf_vlan_push_prio(a);
		attr->vlan_proto[vlan_idx] = tcf_vlan_push_proto(a);
		if (!attr->vlan_proto[vlan_idx])
			attr->vlan_proto[vlan_idx] = htons(ETH_P_8021Q);

		if (vlan_idx) {
			if (!mlx5_eswitch_vlan_actions_supported(priv->mdev,
								 MLX5_FS_VLAN_DEPTH))
				return -EOPNOTSUPP;

			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2;
		} else {
			if (!mlx5_eswitch_vlan_actions_supported(priv->mdev, 1) &&
			    (tcf_vlan_push_proto(a) != htons(ETH_P_8021Q) ||
			     tcf_vlan_push_prio(a)))
				return -EOPNOTSUPP;

			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH;
		}
	} else { /* action is TCA_VLAN_ACT_MODIFY */
		return -EOPNOTSUPP;
	}

	attr->total_vlan = vlan_idx + 1;

	return 0;
}