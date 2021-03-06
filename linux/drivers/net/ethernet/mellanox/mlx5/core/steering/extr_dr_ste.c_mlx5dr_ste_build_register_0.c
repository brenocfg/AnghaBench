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
struct mlx5dr_ste_build {int rx; int inner; int /*<<< orphan*/ * ste_build_tag_func; int /*<<< orphan*/  bit_mask; int /*<<< orphan*/  byte_mask; int /*<<< orphan*/  lu_type; } ;
struct mlx5dr_match_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5DR_STE_LU_TYPE_STEERING_REGISTERS_0 ; 
 int /*<<< orphan*/  dr_ste_build_register_0_bit_mask (struct mlx5dr_match_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_ste_build_register_0_tag ; 
 int /*<<< orphan*/  dr_ste_conv_bit_to_byte_mask (int /*<<< orphan*/ ) ; 

void mlx5dr_ste_build_register_0(struct mlx5dr_ste_build *sb,
				 struct mlx5dr_match_param *mask,
				 bool inner, bool rx)
{
	dr_ste_build_register_0_bit_mask(mask, sb->bit_mask);

	sb->rx = rx;
	sb->inner = inner;
	sb->lu_type = MLX5DR_STE_LU_TYPE_STEERING_REGISTERS_0;
	sb->byte_mask = dr_ste_conv_bit_to_byte_mask(sb->bit_mask);
	sb->ste_build_tag_func = &dr_ste_build_register_0_tag;
}