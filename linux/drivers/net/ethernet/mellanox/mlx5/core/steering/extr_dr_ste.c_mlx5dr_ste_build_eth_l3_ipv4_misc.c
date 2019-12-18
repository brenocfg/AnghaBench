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
 int /*<<< orphan*/  DR_STE_CALC_LU_TYPE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ETHL3_IPV4_MISC ; 
 int /*<<< orphan*/  dr_ste_build_eth_l3_ipv4_misc_bit_mask (struct mlx5dr_match_param*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_ste_build_eth_l3_ipv4_misc_tag ; 
 int /*<<< orphan*/  dr_ste_conv_bit_to_byte_mask (int /*<<< orphan*/ ) ; 

void mlx5dr_ste_build_eth_l3_ipv4_misc(struct mlx5dr_ste_build *sb,
				       struct mlx5dr_match_param *mask,
				       bool inner, bool rx)
{
	dr_ste_build_eth_l3_ipv4_misc_bit_mask(mask, inner, sb->bit_mask);

	sb->rx = rx;
	sb->inner = inner;
	sb->lu_type = DR_STE_CALC_LU_TYPE(ETHL3_IPV4_MISC, rx, inner);
	sb->byte_mask = dr_ste_conv_bit_to_byte_mask(sb->bit_mask);
	sb->ste_build_tag_func = &dr_ste_build_eth_l3_ipv4_misc_tag;
}