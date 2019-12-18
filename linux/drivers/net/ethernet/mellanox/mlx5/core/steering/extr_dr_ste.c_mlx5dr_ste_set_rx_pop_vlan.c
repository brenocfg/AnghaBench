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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_TUNL_ACTION_POP_VLAN ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ste_rx_steering_mult ; 
 int /*<<< orphan*/  tunneling_action ; 

void mlx5dr_ste_set_rx_pop_vlan(u8 *hw_ste_p)
{
	MLX5_SET(ste_rx_steering_mult, hw_ste_p, tunneling_action,
		 DR_STE_TUNL_ACTION_POP_VLAN);
}