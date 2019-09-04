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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int MLX5E_LINK_MODES_NUMBER ; 
 scalar_t__ MLX5E_PROT_MASK (int) ; 
 scalar_t__* mlx5e_link_speed ; 

u32 mlx5e_port_speed2linkmodes(u32 speed)
{
	u32 link_modes = 0;
	int i;

	for (i = 0; i < MLX5E_LINK_MODES_NUMBER; ++i) {
		if (mlx5e_link_speed[i] == speed)
			link_modes |= MLX5E_PROT_MASK(i);
	}

	return link_modes;
}