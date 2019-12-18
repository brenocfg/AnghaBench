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
struct mlx5dr_match_misc3 {int dummy; } ;
struct mlx5dr_match_param {struct mlx5dr_match_misc3 misc3; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SET_MASK_V (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5dr_match_misc3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ack_num ; 
 int /*<<< orphan*/  eth_l4_misc ; 
 int /*<<< orphan*/  inner_tcp_ack_num ; 
 int /*<<< orphan*/  inner_tcp_seq_num ; 
 int /*<<< orphan*/  outer_tcp_ack_num ; 
 int /*<<< orphan*/  outer_tcp_seq_num ; 
 int /*<<< orphan*/  seq_num ; 

__attribute__((used)) static void dr_ste_build_eth_l4_misc_bit_mask(struct mlx5dr_match_param *value,
					      bool inner, u8 *bit_mask)
{
	struct mlx5dr_match_misc3 *misc_3_mask = &value->misc3;

	if (inner) {
		DR_STE_SET_MASK_V(eth_l4_misc, bit_mask, seq_num, misc_3_mask,
				  inner_tcp_seq_num);
		DR_STE_SET_MASK_V(eth_l4_misc, bit_mask, ack_num, misc_3_mask,
				  inner_tcp_ack_num);
	} else {
		DR_STE_SET_MASK_V(eth_l4_misc, bit_mask, seq_num, misc_3_mask,
				  outer_tcp_seq_num);
		DR_STE_SET_MASK_V(eth_l4_misc, bit_mask, ack_num, misc_3_mask,
				  outer_tcp_ack_num);
	}
}