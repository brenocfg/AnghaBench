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
struct mlx5dr_match_misc3 {int outer_vxlan_gpe_flags; int outer_vxlan_gpe_next_protocol; int outer_vxlan_gpe_vni; } ;
struct mlx5dr_match_param {struct mlx5dr_match_misc3 misc3; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flex_parser_tunneling_header_31_0 ; 
 int /*<<< orphan*/  flex_parser_tunneling_header_63_32 ; 
 int /*<<< orphan*/  ste_flex_parser_tnl ; 

__attribute__((used)) static void dr_ste_build_flex_parser_tnl_bit_mask(struct mlx5dr_match_param *value,
						  bool inner, u8 *bit_mask)
{
	struct mlx5dr_match_misc3 *misc_3_mask = &value->misc3;

	if (misc_3_mask->outer_vxlan_gpe_flags ||
	    misc_3_mask->outer_vxlan_gpe_next_protocol) {
		MLX5_SET(ste_flex_parser_tnl, bit_mask,
			 flex_parser_tunneling_header_63_32,
			 (misc_3_mask->outer_vxlan_gpe_flags << 24) |
			 (misc_3_mask->outer_vxlan_gpe_next_protocol));
		misc_3_mask->outer_vxlan_gpe_flags = 0;
		misc_3_mask->outer_vxlan_gpe_next_protocol = 0;
	}

	if (misc_3_mask->outer_vxlan_gpe_vni) {
		MLX5_SET(ste_flex_parser_tnl, bit_mask,
			 flex_parser_tunneling_header_31_0,
			 misc_3_mask->outer_vxlan_gpe_vni << 8);
		misc_3_mask->outer_vxlan_gpe_vni = 0;
	}
}