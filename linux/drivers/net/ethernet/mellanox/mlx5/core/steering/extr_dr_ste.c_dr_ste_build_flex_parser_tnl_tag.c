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
struct mlx5dr_ste_build {int dummy; } ;
struct mlx5dr_match_misc3 {int outer_vxlan_gpe_flags; int outer_vxlan_gpe_next_protocol; int outer_vxlan_gpe_vni; } ;
struct mlx5dr_match_param {struct mlx5dr_match_misc3 misc3; } ;
struct dr_hw_ste_format {int /*<<< orphan*/ * tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flex_parser_tunneling_header_31_0 ; 
 int /*<<< orphan*/  flex_parser_tunneling_header_63_32 ; 
 int /*<<< orphan*/  ste_flex_parser_tnl ; 

__attribute__((used)) static int dr_ste_build_flex_parser_tnl_tag(struct mlx5dr_match_param *value,
					    struct mlx5dr_ste_build *sb,
					    u8 *hw_ste_p)
{
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)hw_ste_p;
	struct mlx5dr_match_misc3 *misc3 = &value->misc3;
	u8 *tag = hw_ste->tag;

	if (misc3->outer_vxlan_gpe_flags ||
	    misc3->outer_vxlan_gpe_next_protocol) {
		MLX5_SET(ste_flex_parser_tnl, tag,
			 flex_parser_tunneling_header_63_32,
			 (misc3->outer_vxlan_gpe_flags << 24) |
			 (misc3->outer_vxlan_gpe_next_protocol));
		misc3->outer_vxlan_gpe_flags = 0;
		misc3->outer_vxlan_gpe_next_protocol = 0;
	}

	if (misc3->outer_vxlan_gpe_vni) {
		MLX5_SET(ste_flex_parser_tnl, tag,
			 flex_parser_tunneling_header_31_0,
			 misc3->outer_vxlan_gpe_vni << 8);
		misc3->outer_vxlan_gpe_vni = 0;
	}

	return 0;
}