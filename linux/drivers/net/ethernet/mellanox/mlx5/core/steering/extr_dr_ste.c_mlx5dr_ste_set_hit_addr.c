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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next_table_base_31_5_size ; 
 int /*<<< orphan*/  next_table_base_39_32_size ; 
 int /*<<< orphan*/  ste_general ; 

void mlx5dr_ste_set_hit_addr(u8 *hw_ste, u64 icm_addr, u32 ht_size)
{
	u64 index = (icm_addr >> 5) | ht_size;

	MLX5_SET(ste_general, hw_ste, next_table_base_39_32_size, index >> 27);
	MLX5_SET(ste_general, hw_ste, next_table_base_31_5_size, index);
}