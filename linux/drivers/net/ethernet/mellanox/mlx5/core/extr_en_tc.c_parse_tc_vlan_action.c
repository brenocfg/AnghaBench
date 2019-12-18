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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct mlx5_esw_flow_attr {scalar_t__ total_vlan; int /*<<< orphan*/ * vlan_proto; int /*<<< orphan*/ * vlan_prio; int /*<<< orphan*/ * vlan_vid; } ;
struct TYPE_2__ {int /*<<< orphan*/  prio; int /*<<< orphan*/  proto; int /*<<< orphan*/  vid; } ;
struct flow_action_entry {int id; TYPE_1__ vlan; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
#define  FLOW_ACTION_VLAN_POP 129 
#define  FLOW_ACTION_VLAN_PUSH 128 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_VLAN_POP ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_VLAN_POP_2 ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2 ; 
 scalar_t__ MLX5_FS_VLAN_DEPTH ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_eswitch_vlan_actions_supported (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int parse_tc_vlan_action(struct mlx5e_priv *priv,
				const struct flow_action_entry *act,
				struct mlx5_esw_flow_attr *attr,
				u32 *action)
{
	u8 vlan_idx = attr->total_vlan;

	if (vlan_idx >= MLX5_FS_VLAN_DEPTH)
		return -EOPNOTSUPP;

	switch (act->id) {
	case FLOW_ACTION_VLAN_POP:
		if (vlan_idx) {
			if (!mlx5_eswitch_vlan_actions_supported(priv->mdev,
								 MLX5_FS_VLAN_DEPTH))
				return -EOPNOTSUPP;

			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_POP_2;
		} else {
			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_POP;
		}
		break;
	case FLOW_ACTION_VLAN_PUSH:
		attr->vlan_vid[vlan_idx] = act->vlan.vid;
		attr->vlan_prio[vlan_idx] = act->vlan.prio;
		attr->vlan_proto[vlan_idx] = act->vlan.proto;
		if (!attr->vlan_proto[vlan_idx])
			attr->vlan_proto[vlan_idx] = htons(ETH_P_8021Q);

		if (vlan_idx) {
			if (!mlx5_eswitch_vlan_actions_supported(priv->mdev,
								 MLX5_FS_VLAN_DEPTH))
				return -EOPNOTSUPP;

			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2;
		} else {
			if (!mlx5_eswitch_vlan_actions_supported(priv->mdev, 1) &&
			    (act->vlan.proto != htons(ETH_P_8021Q) ||
			     act->vlan.prio))
				return -EOPNOTSUPP;

			*action |= MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH;
		}
		break;
	default:
		return -EINVAL;
	}

	attr->total_vlan = vlan_idx + 1;

	return 0;
}