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
struct mlx5dr_match_misc2 {int dummy; } ;
struct mlx5dr_match_param {struct mlx5dr_match_misc2 misc2; } ;
struct dr_hw_ste_format {int /*<<< orphan*/ * tag; } ;

/* Variables and functions */
 scalar_t__ DR_STE_IS_OUTER_MPLS_OVER_GRE_SET (struct mlx5dr_match_misc2*) ; 
 int /*<<< orphan*/  DR_STE_SET_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5dr_match_misc2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flex_parser_0 ; 
 int /*<<< orphan*/  outer_first_mpls_over_gre_exp ; 
 int /*<<< orphan*/  outer_first_mpls_over_gre_label ; 
 int /*<<< orphan*/  outer_first_mpls_over_gre_s_bos ; 
 int /*<<< orphan*/  outer_first_mpls_over_gre_ttl ; 
 int /*<<< orphan*/  outer_first_mpls_over_udp_exp ; 
 int /*<<< orphan*/  outer_first_mpls_over_udp_label ; 
 int /*<<< orphan*/  outer_first_mpls_over_udp_s_bos ; 
 int /*<<< orphan*/  outer_first_mpls_over_udp_ttl ; 
 int /*<<< orphan*/  parser_3_exp ; 
 int /*<<< orphan*/  parser_3_label ; 
 int /*<<< orphan*/  parser_3_s_bos ; 
 int /*<<< orphan*/  parser_3_ttl ; 

__attribute__((used)) static int dr_ste_build_flex_parser_0_tag(struct mlx5dr_match_param *value,
					  struct mlx5dr_ste_build *sb,
					  u8 *hw_ste_p)
{
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)hw_ste_p;
	struct mlx5dr_match_misc2 *misc_2_mask = &value->misc2;
	u8 *tag = hw_ste->tag;

	if (DR_STE_IS_OUTER_MPLS_OVER_GRE_SET(misc_2_mask)) {
		DR_STE_SET_TAG(flex_parser_0, tag, parser_3_label,
			       misc_2_mask, outer_first_mpls_over_gre_label);

		DR_STE_SET_TAG(flex_parser_0, tag, parser_3_exp,
			       misc_2_mask, outer_first_mpls_over_gre_exp);

		DR_STE_SET_TAG(flex_parser_0, tag, parser_3_s_bos,
			       misc_2_mask, outer_first_mpls_over_gre_s_bos);

		DR_STE_SET_TAG(flex_parser_0, tag, parser_3_ttl,
			       misc_2_mask, outer_first_mpls_over_gre_ttl);
	} else {
		DR_STE_SET_TAG(flex_parser_0, tag, parser_3_label,
			       misc_2_mask, outer_first_mpls_over_udp_label);

		DR_STE_SET_TAG(flex_parser_0, tag, parser_3_exp,
			       misc_2_mask, outer_first_mpls_over_udp_exp);

		DR_STE_SET_TAG(flex_parser_0, tag, parser_3_s_bos,
			       misc_2_mask, outer_first_mpls_over_udp_s_bos);

		DR_STE_SET_TAG(flex_parser_0, tag, parser_3_ttl,
			       misc_2_mask, outer_first_mpls_over_udp_ttl);
	}
	return 0;
}