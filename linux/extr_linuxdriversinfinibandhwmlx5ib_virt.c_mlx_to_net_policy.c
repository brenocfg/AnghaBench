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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum port_state_policy { ____Placeholder_port_state_policy } port_state_policy ;

/* Variables and functions */
 int /*<<< orphan*/  IFLA_VF_LINK_STATE_AUTO ; 
 int /*<<< orphan*/  IFLA_VF_LINK_STATE_DISABLE ; 
 int /*<<< orphan*/  IFLA_VF_LINK_STATE_ENABLE ; 
#define  MLX5_POLICY_DOWN 130 
#define  MLX5_POLICY_FOLLOW 129 
#define  MLX5_POLICY_UP 128 
 int /*<<< orphan*/  __IFLA_VF_LINK_STATE_MAX ; 

__attribute__((used)) static inline u32 mlx_to_net_policy(enum port_state_policy mlx_policy)
{
	switch (mlx_policy) {
	case MLX5_POLICY_DOWN:
		return IFLA_VF_LINK_STATE_DISABLE;
	case MLX5_POLICY_UP:
		return IFLA_VF_LINK_STATE_ENABLE;
	case MLX5_POLICY_FOLLOW:
		return IFLA_VF_LINK_STATE_AUTO;
	default:
		return __IFLA_VF_LINK_STATE_MAX;
	}
}