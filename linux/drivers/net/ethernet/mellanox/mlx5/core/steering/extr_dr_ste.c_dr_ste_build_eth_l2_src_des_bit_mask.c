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
struct mlx5dr_match_spec {int smac_47_16; int smac_15_0; scalar_t__ svlan_tag; scalar_t__ cvlan_tag; } ;
struct mlx5dr_match_param {struct mlx5dr_match_spec outer; struct mlx5dr_match_spec inner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5dr_match_spec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DR_STE_SET_MASK_V (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5dr_match_spec*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmac_15_0 ; 
 int /*<<< orphan*/  dmac_47_16 ; 
 int /*<<< orphan*/  eth_l2_src_dst ; 
 int /*<<< orphan*/  first_cfi ; 
 int /*<<< orphan*/  first_prio ; 
 int /*<<< orphan*/  first_priority ; 
 int /*<<< orphan*/  first_vid ; 
 int /*<<< orphan*/  first_vlan_id ; 
 int /*<<< orphan*/  first_vlan_qualifier ; 
 int /*<<< orphan*/  ip_version ; 
 int /*<<< orphan*/  l3_type ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  smac_31_0 ; 
 int /*<<< orphan*/  smac_47_32 ; 
 int /*<<< orphan*/  ste_eth_l2_src_dst ; 

__attribute__((used)) static int dr_ste_build_eth_l2_src_des_bit_mask(struct mlx5dr_match_param *value,
						bool inner, u8 *bit_mask)
{
	struct mlx5dr_match_spec *mask = inner ? &value->inner : &value->outer;

	DR_STE_SET_MASK_V(eth_l2_src_dst, bit_mask, dmac_47_16, mask, dmac_47_16);
	DR_STE_SET_MASK_V(eth_l2_src_dst, bit_mask, dmac_15_0, mask, dmac_15_0);

	if (mask->smac_47_16 || mask->smac_15_0) {
		MLX5_SET(ste_eth_l2_src_dst, bit_mask, smac_47_32,
			 mask->smac_47_16 >> 16);
		MLX5_SET(ste_eth_l2_src_dst, bit_mask, smac_31_0,
			 mask->smac_47_16 << 16 | mask->smac_15_0);
		mask->smac_47_16 = 0;
		mask->smac_15_0 = 0;
	}

	DR_STE_SET_MASK_V(eth_l2_src_dst, bit_mask, first_vlan_id, mask, first_vid);
	DR_STE_SET_MASK_V(eth_l2_src_dst, bit_mask, first_cfi, mask, first_cfi);
	DR_STE_SET_MASK_V(eth_l2_src_dst, bit_mask, first_priority, mask, first_prio);
	DR_STE_SET_MASK(eth_l2_src_dst, bit_mask, l3_type, mask, ip_version);

	if (mask->cvlan_tag) {
		MLX5_SET(ste_eth_l2_src_dst, bit_mask, first_vlan_qualifier, -1);
		mask->cvlan_tag = 0;
	} else if (mask->svlan_tag) {
		MLX5_SET(ste_eth_l2_src_dst, bit_mask, first_vlan_qualifier, -1);
		mask->svlan_tag = 0;
	}

	if (mask->cvlan_tag || mask->svlan_tag) {
		pr_info("Invalid c/svlan mask configuration\n");
		return -EINVAL;
	}

	return 0;
}