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
typedef  unsigned long u32 ;

/* Variables and functions */
 int MLX5E_LINK_MODES_NUMBER ; 
 int find_first_bit (unsigned long*,int) ; 
 unsigned long* mlx5e_link_speed ; 

u32 mlx5e_port_ptys2speed(u32 eth_proto_oper)
{
	unsigned long temp = eth_proto_oper;
	u32 speed = 0;
	int i;

	i = find_first_bit(&temp, MLX5E_LINK_MODES_NUMBER);
	if (i < MLX5E_LINK_MODES_NUMBER)
		speed = mlx5e_link_speed[i];

	return speed;
}