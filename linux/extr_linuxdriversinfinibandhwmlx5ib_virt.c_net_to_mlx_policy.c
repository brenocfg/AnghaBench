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
typedef  enum port_state_policy { ____Placeholder_port_state_policy } port_state_policy ;

/* Variables and functions */
#define  IFLA_VF_LINK_STATE_AUTO 130 
#define  IFLA_VF_LINK_STATE_DISABLE 129 
#define  IFLA_VF_LINK_STATE_ENABLE 128 
 int MLX5_POLICY_DOWN ; 
 int MLX5_POLICY_FOLLOW ; 
 int MLX5_POLICY_INVALID ; 
 int MLX5_POLICY_UP ; 

__attribute__((used)) static inline enum port_state_policy net_to_mlx_policy(int policy)
{
	switch (policy) {
	case IFLA_VF_LINK_STATE_DISABLE:
		return MLX5_POLICY_DOWN;
	case IFLA_VF_LINK_STATE_ENABLE:
		return MLX5_POLICY_UP;
	case IFLA_VF_LINK_STATE_AUTO:
		return MLX5_POLICY_FOLLOW;
	default:
		return MLX5_POLICY_INVALID;
	}
}