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
#define  DEVLINK_ESWITCH_INLINE_MODE_LINK 131 
#define  DEVLINK_ESWITCH_INLINE_MODE_NETWORK 130 
#define  DEVLINK_ESWITCH_INLINE_MODE_NONE 129 
#define  DEVLINK_ESWITCH_INLINE_MODE_TRANSPORT 128 
 int EINVAL ; 
 int MLX5_INLINE_MODE_IP ; 
 int MLX5_INLINE_MODE_L2 ; 
 int MLX5_INLINE_MODE_NONE ; 
 int MLX5_INLINE_MODE_TCP_UDP ; 

__attribute__((used)) static int esw_inline_mode_from_devlink(u8 mode, u8 *mlx5_mode)
{
	switch (mode) {
	case DEVLINK_ESWITCH_INLINE_MODE_NONE:
		*mlx5_mode = MLX5_INLINE_MODE_NONE;
		break;
	case DEVLINK_ESWITCH_INLINE_MODE_LINK:
		*mlx5_mode = MLX5_INLINE_MODE_L2;
		break;
	case DEVLINK_ESWITCH_INLINE_MODE_NETWORK:
		*mlx5_mode = MLX5_INLINE_MODE_IP;
		break;
	case DEVLINK_ESWITCH_INLINE_MODE_TRANSPORT:
		*mlx5_mode = MLX5_INLINE_MODE_TCP_UDP;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}