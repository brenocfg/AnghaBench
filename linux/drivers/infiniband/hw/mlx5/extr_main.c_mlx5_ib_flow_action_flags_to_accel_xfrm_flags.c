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
 int MLX5_ACCEL_XFRM_FLAG_REQUIRE_METADATA ; 
 int MLX5_IB_UAPI_FLOW_ACTION_FLAGS_REQUIRE_METADATA ; 

__attribute__((used)) static u32 mlx5_ib_flow_action_flags_to_accel_xfrm_flags(u32 mlx5_flags)
{
	u32 flags = 0;

	if (mlx5_flags & MLX5_IB_UAPI_FLOW_ACTION_FLAGS_REQUIRE_METADATA)
		flags |= MLX5_ACCEL_XFRM_FLAG_REQUIRE_METADATA;

	return flags;
}