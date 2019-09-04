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

/* Variables and functions */
#define  MLX4_STEERING_DMFS_A0_DEFAULT 132 
#define  MLX4_STEERING_DMFS_A0_DISABLE 131 
#define  MLX4_STEERING_DMFS_A0_DYNAMIC 130 
#define  MLX4_STEERING_DMFS_A0_NOT_SUPPORTED 129 
#define  MLX4_STEERING_DMFS_A0_STATIC 128 

__attribute__((used)) static const char *dmfs_high_rate_steering_mode_str(int dmfs_high_steer_mode)
{
	switch (dmfs_high_steer_mode) {
	case MLX4_STEERING_DMFS_A0_DEFAULT:
		return "default performance";

	case MLX4_STEERING_DMFS_A0_DYNAMIC:
		return "dynamic hybrid mode";

	case MLX4_STEERING_DMFS_A0_STATIC:
		return "performance optimized for limited rule configuration (static)";

	case MLX4_STEERING_DMFS_A0_DISABLE:
		return "disabled performance optimized steering";

	case MLX4_STEERING_DMFS_A0_NOT_SUPPORTED:
		return "performance optimized steering not supported";

	default:
		return "Unrecognized mode";
	}
}