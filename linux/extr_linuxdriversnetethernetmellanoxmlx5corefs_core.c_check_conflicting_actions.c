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
typedef  int u32 ;

/* Variables and functions */
 int MLX5_FLOW_CONTEXT_ACTION_COUNT ; 
 int MLX5_FLOW_CONTEXT_ACTION_DECAP ; 
 int MLX5_FLOW_CONTEXT_ACTION_DROP ; 
 int MLX5_FLOW_CONTEXT_ACTION_ENCAP ; 
 int MLX5_FLOW_CONTEXT_ACTION_MOD_HDR ; 
 int MLX5_FLOW_CONTEXT_ACTION_VLAN_POP ; 
 int MLX5_FLOW_CONTEXT_ACTION_VLAN_POP_2 ; 
 int MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH ; 
 int MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2 ; 

__attribute__((used)) static bool check_conflicting_actions(u32 action1, u32 action2)
{
	u32 xored_actions = action1 ^ action2;

	/* if one rule only wants to count, it's ok */
	if (action1 == MLX5_FLOW_CONTEXT_ACTION_COUNT ||
	    action2 == MLX5_FLOW_CONTEXT_ACTION_COUNT)
		return false;

	if (xored_actions & (MLX5_FLOW_CONTEXT_ACTION_DROP  |
			     MLX5_FLOW_CONTEXT_ACTION_ENCAP |
			     MLX5_FLOW_CONTEXT_ACTION_DECAP |
			     MLX5_FLOW_CONTEXT_ACTION_MOD_HDR  |
			     MLX5_FLOW_CONTEXT_ACTION_VLAN_POP |
			     MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH |
			     MLX5_FLOW_CONTEXT_ACTION_VLAN_POP_2 |
			     MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH_2))
		return true;

	return false;
}