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
struct mlx5dr_match_spec {scalar_t__ ip_version; scalar_t__ outer_second_svlan_tag; scalar_t__ outer_second_cvlan_tag; scalar_t__ inner_second_svlan_tag; scalar_t__ inner_second_cvlan_tag; scalar_t__ svlan_tag; scalar_t__ cvlan_tag; } ;
struct mlx5dr_match_param {struct mlx5dr_match_spec misc; struct mlx5dr_match_spec outer; struct mlx5dr_match_spec inner; } ;
struct mlx5dr_match_misc {scalar_t__ ip_version; scalar_t__ outer_second_svlan_tag; scalar_t__ outer_second_cvlan_tag; scalar_t__ inner_second_svlan_tag; scalar_t__ inner_second_cvlan_tag; scalar_t__ svlan_tag; scalar_t__ cvlan_tag; } ;
struct dr_hw_ste_format {int /*<<< orphan*/ * tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_CVLAN ; 
 int /*<<< orphan*/  DR_STE_SET_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5dr_match_spec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DR_STE_SVLAN ; 
 int EINVAL ; 
 scalar_t__ IP_VERSION_IPV4 ; 
 scalar_t__ IP_VERSION_IPV6 ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STE_IPV4 ; 
 int /*<<< orphan*/  STE_IPV6 ; 
 int /*<<< orphan*/  eth_l2_src ; 
 int /*<<< orphan*/  ethertype ; 
 int /*<<< orphan*/  first_cfi ; 
 int /*<<< orphan*/  first_prio ; 
 int /*<<< orphan*/  first_priority ; 
 int /*<<< orphan*/  first_vid ; 
 int /*<<< orphan*/  first_vlan_id ; 
 int /*<<< orphan*/  first_vlan_qualifier ; 
 int /*<<< orphan*/  frag ; 
 int /*<<< orphan*/  inner_second_cfi ; 
 int /*<<< orphan*/  inner_second_prio ; 
 int /*<<< orphan*/  inner_second_vid ; 
 int /*<<< orphan*/  ip_fragmented ; 
 int /*<<< orphan*/  l3_ethertype ; 
 int /*<<< orphan*/  l3_type ; 
 int /*<<< orphan*/  outer_second_cfi ; 
 int /*<<< orphan*/  outer_second_prio ; 
 int /*<<< orphan*/  outer_second_vid ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  second_cfi ; 
 int /*<<< orphan*/  second_priority ; 
 int /*<<< orphan*/  second_vlan_id ; 
 int /*<<< orphan*/  second_vlan_qualifier ; 
 int /*<<< orphan*/  ste_eth_l2_src ; 

__attribute__((used)) static int dr_ste_build_eth_l2_src_or_dst_tag(struct mlx5dr_match_param *value,
					      bool inner, u8 *hw_ste_p)
{
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)hw_ste_p;
	struct mlx5dr_match_spec *spec = inner ? &value->inner : &value->outer;
	struct mlx5dr_match_misc *misc_spec = &value->misc;
	u8 *tag = hw_ste->tag;

	DR_STE_SET_TAG(eth_l2_src, tag, first_vlan_id, spec, first_vid);
	DR_STE_SET_TAG(eth_l2_src, tag, first_cfi, spec, first_cfi);
	DR_STE_SET_TAG(eth_l2_src, tag, first_priority, spec, first_prio);
	DR_STE_SET_TAG(eth_l2_src, tag, ip_fragmented, spec, frag);
	DR_STE_SET_TAG(eth_l2_src, tag, l3_ethertype, spec, ethertype);

	if (spec->ip_version) {
		if (spec->ip_version == IP_VERSION_IPV4) {
			MLX5_SET(ste_eth_l2_src, tag, l3_type, STE_IPV4);
			spec->ip_version = 0;
		} else if (spec->ip_version == IP_VERSION_IPV6) {
			MLX5_SET(ste_eth_l2_src, tag, l3_type, STE_IPV6);
			spec->ip_version = 0;
		} else {
			pr_info("Unsupported ip_version value\n");
			return -EINVAL;
		}
	}

	if (spec->cvlan_tag) {
		MLX5_SET(ste_eth_l2_src, tag, first_vlan_qualifier, DR_STE_CVLAN);
		spec->cvlan_tag = 0;
	} else if (spec->svlan_tag) {
		MLX5_SET(ste_eth_l2_src, tag, first_vlan_qualifier, DR_STE_SVLAN);
		spec->svlan_tag = 0;
	}

	if (inner) {
		if (misc_spec->inner_second_cvlan_tag) {
			MLX5_SET(ste_eth_l2_src, tag, second_vlan_qualifier, DR_STE_CVLAN);
			misc_spec->inner_second_cvlan_tag = 0;
		} else if (misc_spec->inner_second_svlan_tag) {
			MLX5_SET(ste_eth_l2_src, tag, second_vlan_qualifier, DR_STE_SVLAN);
			misc_spec->inner_second_svlan_tag = 0;
		}

		DR_STE_SET_TAG(eth_l2_src, tag, second_vlan_id, misc_spec, inner_second_vid);
		DR_STE_SET_TAG(eth_l2_src, tag, second_cfi, misc_spec, inner_second_cfi);
		DR_STE_SET_TAG(eth_l2_src, tag, second_priority, misc_spec, inner_second_prio);
	} else {
		if (misc_spec->outer_second_cvlan_tag) {
			MLX5_SET(ste_eth_l2_src, tag, second_vlan_qualifier, DR_STE_CVLAN);
			misc_spec->outer_second_cvlan_tag = 0;
		} else if (misc_spec->outer_second_svlan_tag) {
			MLX5_SET(ste_eth_l2_src, tag, second_vlan_qualifier, DR_STE_SVLAN);
			misc_spec->outer_second_svlan_tag = 0;
		}
		DR_STE_SET_TAG(eth_l2_src, tag, second_vlan_id, misc_spec, outer_second_vid);
		DR_STE_SET_TAG(eth_l2_src, tag, second_cfi, misc_spec, outer_second_cfi);
		DR_STE_SET_TAG(eth_l2_src, tag, second_priority, misc_spec, outer_second_prio);
	}

	return 0;
}