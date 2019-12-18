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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  counter_trigger_15_0 ; 
 int /*<<< orphan*/  counter_trigger_23_16 ; 
 int /*<<< orphan*/  ste_rx_steering_mult ; 

void mlx5dr_ste_set_counter_id(u8 *hw_ste_p, u32 ctr_id)
{
	/* This can be used for both rx_steering_mult and for sx_transmit */
	MLX5_SET(ste_rx_steering_mult, hw_ste_p, counter_trigger_15_0, ctr_id);
	MLX5_SET(ste_rx_steering_mult, hw_ste_p, counter_trigger_23_16, ctr_id >> 16);
}