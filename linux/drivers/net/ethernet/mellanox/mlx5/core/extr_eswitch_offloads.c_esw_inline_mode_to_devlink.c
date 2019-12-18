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

/* Variables and functions */
 int DEVLINK_ESWITCH_INLINE_MODE_LINK ; 
 int DEVLINK_ESWITCH_INLINE_MODE_NETWORK ; 
 int DEVLINK_ESWITCH_INLINE_MODE_NONE ; 
 int DEVLINK_ESWITCH_INLINE_MODE_TRANSPORT ; 
 int EINVAL ; 
#define  MLX5_INLINE_MODE_IP 131 
#define  MLX5_INLINE_MODE_L2 130 
#define  MLX5_INLINE_MODE_NONE 129 
#define  MLX5_INLINE_MODE_TCP_UDP 128 

__attribute__((used)) static int esw_inline_mode_to_devlink(u8 mlx5_mode, u8 *mode)
{
	switch (mlx5_mode) {
	case MLX5_INLINE_MODE_NONE:
		*mode = DEVLINK_ESWITCH_INLINE_MODE_NONE;
		break;
	case MLX5_INLINE_MODE_L2:
		*mode = DEVLINK_ESWITCH_INLINE_MODE_LINK;
		break;
	case MLX5_INLINE_MODE_IP:
		*mode = DEVLINK_ESWITCH_INLINE_MODE_NETWORK;
		break;
	case MLX5_INLINE_MODE_TCP_UDP:
		*mode = DEVLINK_ESWITCH_INLINE_MODE_TRANSPORT;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}