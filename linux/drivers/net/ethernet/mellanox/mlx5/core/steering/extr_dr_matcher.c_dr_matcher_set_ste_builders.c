#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct mlx5dr_ste_build {int dummy; } ;
struct mlx5dr_matcher_rx_tx {scalar_t__ num_of_builders6; scalar_t__ num_of_builders4; struct mlx5dr_ste_build* ste_builder4; struct mlx5dr_ste_build* ste_builder6; TYPE_2__* nic_tbl; } ;
struct mlx5dr_match_misc3 {int dummy; } ;
struct TYPE_8__ {struct mlx5dr_match_misc3 misc3; int /*<<< orphan*/  misc2; int /*<<< orphan*/  inner; int /*<<< orphan*/  misc; int /*<<< orphan*/  outer; } ;
struct mlx5dr_matcher {int match_criteria; TYPE_4__ mask; TYPE_3__* tbl; } ;
struct mlx5dr_match_param {int /*<<< orphan*/  misc2; struct mlx5dr_match_misc3 misc3; int /*<<< orphan*/  inner; int /*<<< orphan*/  misc; int /*<<< orphan*/  outer; } ;
struct mlx5dr_domain_rx_tx {scalar_t__ ste_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  caps; } ;
struct mlx5dr_domain {scalar_t__ type; TYPE_1__ info; } ;
struct TYPE_7__ {struct mlx5dr_domain* dmn; } ;
struct TYPE_6__ {struct mlx5dr_domain_rx_tx* nic_dmn; } ;

/* Variables and functions */
 scalar_t__ DR_MASK_IS_ETH_L4_MISC_SET (struct mlx5dr_match_misc3,int) ; 
 scalar_t__ DR_MASK_IS_ETH_L4_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DR_MASK_IS_FIRST_MPLS_SET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ DR_MASK_IS_FLEX_PARSER_0_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ DR_MASK_IS_FLEX_PARSER_ICMPV4_SET (struct mlx5dr_match_misc3*) ; 
 scalar_t__ DR_MASK_IS_L2_DST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int DR_MATCHER_CRITERIA_EMPTY ; 
 int DR_MATCHER_CRITERIA_INNER ; 
 int DR_MATCHER_CRITERIA_MISC ; 
 int DR_MATCHER_CRITERIA_MISC2 ; 
 int DR_MATCHER_CRITERIA_MISC3 ; 
 int DR_MATCHER_CRITERIA_OUTER ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ MLX5DR_DOMAIN_TYPE_FDB ; 
 scalar_t__ MLX5DR_DOMAIN_TYPE_NIC_RX ; 
 scalar_t__ MLX5DR_STE_TYPE_RX ; 
 scalar_t__ dr_mask_is_dmac_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_mask_is_dst_addr_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_mask_is_eth_l2_tnl_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_mask_is_flex_parser_icmpv6_set (struct mlx5dr_match_misc3*) ; 
 scalar_t__ dr_mask_is_flex_parser_tnl_set (struct mlx5dr_match_misc3*) ; 
 scalar_t__ dr_mask_is_gre_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_mask_is_gvmi_or_qpn_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_mask_is_ipv4_5_tuple_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_mask_is_reg_c_0_3_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_mask_is_reg_c_4_7_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_mask_is_smac_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_mask_is_src_addr_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_mask_is_ttl_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_mask_is_wqe_metadata_set (int /*<<< orphan*/ *) ; 
 scalar_t__ dr_matcher_supp_flex_parser_vxlan_gpe (struct mlx5dr_domain*) ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*) ; 
 int /*<<< orphan*/  mlx5dr_info (struct mlx5dr_domain*,char*) ; 
 scalar_t__ mlx5dr_matcher_supp_flex_parser_icmp_v4 (int /*<<< orphan*/ *) ; 
 scalar_t__ mlx5dr_matcher_supp_flex_parser_icmp_v6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_empty_always_hit (struct mlx5dr_ste_build*,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_eth_l2_dst (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_eth_l2_src (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int mlx5dr_ste_build_eth_l2_src_des (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_eth_l2_tnl (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_eth_l3_ipv4_5_tuple (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_eth_l3_ipv4_misc (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_eth_l3_ipv6_dst (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_eth_l3_ipv6_src (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_eth_l4_misc (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_flex_parser_0 (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int mlx5dr_ste_build_flex_parser_1 (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_flex_parser_tnl (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_general_purpose (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_gre (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_ipv6_l3_l4 (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_mpls (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int mlx5dr_ste_build_pre_check (struct mlx5dr_domain*,int,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_register_0 (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_build_register_1 (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,int,int) ; 
 int mlx5dr_ste_build_src_gvmi_qpn (struct mlx5dr_ste_build*,struct mlx5dr_match_param*,struct mlx5dr_domain*,int,int) ; 
 int outer ; 

__attribute__((used)) static int dr_matcher_set_ste_builders(struct mlx5dr_matcher *matcher,
				       struct mlx5dr_matcher_rx_tx *nic_matcher,
				       bool ipv6)
{
	struct mlx5dr_domain_rx_tx *nic_dmn = nic_matcher->nic_tbl->nic_dmn;
	struct mlx5dr_domain *dmn = matcher->tbl->dmn;
	struct mlx5dr_match_param mask = {};
	struct mlx5dr_match_misc3 *misc3;
	struct mlx5dr_ste_build *sb;
	u8 *num_of_builders;
	bool inner, rx;
	int idx = 0;
	int ret, i;

	if (ipv6) {
		sb = nic_matcher->ste_builder6;
		num_of_builders = &nic_matcher->num_of_builders6;
	} else {
		sb = nic_matcher->ste_builder4;
		num_of_builders = &nic_matcher->num_of_builders4;
	}

	rx = nic_dmn->ste_type == MLX5DR_STE_TYPE_RX;

	/* Create a temporary mask to track and clear used mask fields */
	if (matcher->match_criteria & DR_MATCHER_CRITERIA_OUTER)
		mask.outer = matcher->mask.outer;

	if (matcher->match_criteria & DR_MATCHER_CRITERIA_MISC)
		mask.misc = matcher->mask.misc;

	if (matcher->match_criteria & DR_MATCHER_CRITERIA_INNER)
		mask.inner = matcher->mask.inner;

	if (matcher->match_criteria & DR_MATCHER_CRITERIA_MISC2)
		mask.misc2 = matcher->mask.misc2;

	if (matcher->match_criteria & DR_MATCHER_CRITERIA_MISC3)
		mask.misc3 = matcher->mask.misc3;

	ret = mlx5dr_ste_build_pre_check(dmn, matcher->match_criteria,
					 &matcher->mask, NULL);
	if (ret)
		return ret;

	/* Outer */
	if (matcher->match_criteria & (DR_MATCHER_CRITERIA_OUTER |
				       DR_MATCHER_CRITERIA_MISC |
				       DR_MATCHER_CRITERIA_MISC2 |
				       DR_MATCHER_CRITERIA_MISC3)) {
		inner = false;

		if (dr_mask_is_wqe_metadata_set(&mask.misc2))
			mlx5dr_ste_build_general_purpose(&sb[idx++], &mask, inner, rx);

		if (dr_mask_is_reg_c_0_3_set(&mask.misc2))
			mlx5dr_ste_build_register_0(&sb[idx++], &mask, inner, rx);

		if (dr_mask_is_reg_c_4_7_set(&mask.misc2))
			mlx5dr_ste_build_register_1(&sb[idx++], &mask, inner, rx);

		if (dr_mask_is_gvmi_or_qpn_set(&mask.misc) &&
		    (dmn->type == MLX5DR_DOMAIN_TYPE_FDB ||
		     dmn->type == MLX5DR_DOMAIN_TYPE_NIC_RX)) {
			ret = mlx5dr_ste_build_src_gvmi_qpn(&sb[idx++], &mask,
							    dmn, inner, rx);
			if (ret)
				return ret;
		}

		if (dr_mask_is_smac_set(&mask.outer) &&
		    dr_mask_is_dmac_set(&mask.outer)) {
			ret = mlx5dr_ste_build_eth_l2_src_des(&sb[idx++], &mask,
							      inner, rx);
			if (ret)
				return ret;
		}

		if (dr_mask_is_smac_set(&mask.outer))
			mlx5dr_ste_build_eth_l2_src(&sb[idx++], &mask, inner, rx);

		if (DR_MASK_IS_L2_DST(mask.outer, mask.misc, outer))
			mlx5dr_ste_build_eth_l2_dst(&sb[idx++], &mask, inner, rx);

		if (ipv6) {
			if (dr_mask_is_dst_addr_set(&mask.outer))
				mlx5dr_ste_build_eth_l3_ipv6_dst(&sb[idx++], &mask,
								 inner, rx);

			if (dr_mask_is_src_addr_set(&mask.outer))
				mlx5dr_ste_build_eth_l3_ipv6_src(&sb[idx++], &mask,
								 inner, rx);

			if (DR_MASK_IS_ETH_L4_SET(mask.outer, mask.misc, outer))
				mlx5dr_ste_build_ipv6_l3_l4(&sb[idx++], &mask,
							    inner, rx);
		} else {
			if (dr_mask_is_ipv4_5_tuple_set(&mask.outer))
				mlx5dr_ste_build_eth_l3_ipv4_5_tuple(&sb[idx++], &mask,
								     inner, rx);

			if (dr_mask_is_ttl_set(&mask.outer))
				mlx5dr_ste_build_eth_l3_ipv4_misc(&sb[idx++], &mask,
								  inner, rx);
		}

		if (dr_mask_is_flex_parser_tnl_set(&mask.misc3) &&
		    dr_matcher_supp_flex_parser_vxlan_gpe(dmn))
			mlx5dr_ste_build_flex_parser_tnl(&sb[idx++], &mask,
							 inner, rx);

		if (DR_MASK_IS_ETH_L4_MISC_SET(mask.misc3, outer))
			mlx5dr_ste_build_eth_l4_misc(&sb[idx++], &mask, inner, rx);

		if (DR_MASK_IS_FIRST_MPLS_SET(mask.misc2, outer))
			mlx5dr_ste_build_mpls(&sb[idx++], &mask, inner, rx);

		if (DR_MASK_IS_FLEX_PARSER_0_SET(mask.misc2))
			mlx5dr_ste_build_flex_parser_0(&sb[idx++], &mask,
						       inner, rx);

		misc3 = &mask.misc3;
		if ((DR_MASK_IS_FLEX_PARSER_ICMPV4_SET(misc3) &&
		     mlx5dr_matcher_supp_flex_parser_icmp_v4(&dmn->info.caps)) ||
		    (dr_mask_is_flex_parser_icmpv6_set(&mask.misc3) &&
		     mlx5dr_matcher_supp_flex_parser_icmp_v6(&dmn->info.caps))) {
			ret = mlx5dr_ste_build_flex_parser_1(&sb[idx++],
							     &mask, &dmn->info.caps,
							     inner, rx);
			if (ret)
				return ret;
		}
		if (dr_mask_is_gre_set(&mask.misc))
			mlx5dr_ste_build_gre(&sb[idx++], &mask, inner, rx);
	}

	/* Inner */
	if (matcher->match_criteria & (DR_MATCHER_CRITERIA_INNER |
				       DR_MATCHER_CRITERIA_MISC |
				       DR_MATCHER_CRITERIA_MISC2 |
				       DR_MATCHER_CRITERIA_MISC3)) {
		inner = true;

		if (dr_mask_is_eth_l2_tnl_set(&mask.misc))
			mlx5dr_ste_build_eth_l2_tnl(&sb[idx++], &mask, inner, rx);

		if (dr_mask_is_smac_set(&mask.inner) &&
		    dr_mask_is_dmac_set(&mask.inner)) {
			ret = mlx5dr_ste_build_eth_l2_src_des(&sb[idx++],
							      &mask, inner, rx);
			if (ret)
				return ret;
		}

		if (dr_mask_is_smac_set(&mask.inner))
			mlx5dr_ste_build_eth_l2_src(&sb[idx++], &mask, inner, rx);

		if (DR_MASK_IS_L2_DST(mask.inner, mask.misc, inner))
			mlx5dr_ste_build_eth_l2_dst(&sb[idx++], &mask, inner, rx);

		if (ipv6) {
			if (dr_mask_is_dst_addr_set(&mask.inner))
				mlx5dr_ste_build_eth_l3_ipv6_dst(&sb[idx++], &mask,
								 inner, rx);

			if (dr_mask_is_src_addr_set(&mask.inner))
				mlx5dr_ste_build_eth_l3_ipv6_src(&sb[idx++], &mask,
								 inner, rx);

			if (DR_MASK_IS_ETH_L4_SET(mask.inner, mask.misc, inner))
				mlx5dr_ste_build_ipv6_l3_l4(&sb[idx++], &mask,
							    inner, rx);
		} else {
			if (dr_mask_is_ipv4_5_tuple_set(&mask.inner))
				mlx5dr_ste_build_eth_l3_ipv4_5_tuple(&sb[idx++], &mask,
								     inner, rx);

			if (dr_mask_is_ttl_set(&mask.inner))
				mlx5dr_ste_build_eth_l3_ipv4_misc(&sb[idx++], &mask,
								  inner, rx);
		}

		if (DR_MASK_IS_ETH_L4_MISC_SET(mask.misc3, inner))
			mlx5dr_ste_build_eth_l4_misc(&sb[idx++], &mask, inner, rx);

		if (DR_MASK_IS_FIRST_MPLS_SET(mask.misc2, inner))
			mlx5dr_ste_build_mpls(&sb[idx++], &mask, inner, rx);

		if (DR_MASK_IS_FLEX_PARSER_0_SET(mask.misc2))
			mlx5dr_ste_build_flex_parser_0(&sb[idx++], &mask, inner, rx);
	}
	/* Empty matcher, takes all */
	if (matcher->match_criteria == DR_MATCHER_CRITERIA_EMPTY)
		mlx5dr_ste_build_empty_always_hit(&sb[idx++], rx);

	if (idx == 0) {
		mlx5dr_dbg(dmn, "Cannot generate any valid rules from mask\n");
		return -EINVAL;
	}

	/* Check that all mask fields were consumed */
	for (i = 0; i < sizeof(struct mlx5dr_match_param); i++) {
		if (((u8 *)&mask)[i] != 0) {
			mlx5dr_info(dmn, "Mask contains unsupported parameters\n");
			return -EOPNOTSUPP;
		}
	}

	*num_of_builders = idx;

	return 0;
}