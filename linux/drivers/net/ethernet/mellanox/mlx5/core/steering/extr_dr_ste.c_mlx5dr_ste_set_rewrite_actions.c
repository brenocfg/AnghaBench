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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  header_re_write_actions_pointer ; 
 int /*<<< orphan*/  number_of_re_write_actions ; 
 int /*<<< orphan*/  ste_modify_packet ; 

void mlx5dr_ste_set_rewrite_actions(u8 *hw_ste_p, u16 num_of_actions,
				    u32 re_write_index)
{
	MLX5_SET(ste_modify_packet, hw_ste_p, number_of_re_write_actions,
		 num_of_actions);
	MLX5_SET(ste_modify_packet, hw_ste_p, header_re_write_actions_pointer,
		 re_write_index);
}