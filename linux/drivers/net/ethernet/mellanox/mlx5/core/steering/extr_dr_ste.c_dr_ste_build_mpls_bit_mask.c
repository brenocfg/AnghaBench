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
struct mlx5dr_match_misc2 {int dummy; } ;
struct mlx5dr_match_param {struct mlx5dr_match_misc2 misc2; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SET_MPLS_MASK (int /*<<< orphan*/ ,struct mlx5dr_match_misc2*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpls ; 
 int outer ; 

__attribute__((used)) static void dr_ste_build_mpls_bit_mask(struct mlx5dr_match_param *value,
				       bool inner, u8 *bit_mask)
{
	struct mlx5dr_match_misc2 *misc2_mask = &value->misc2;

	if (inner)
		DR_STE_SET_MPLS_MASK(mpls, misc2_mask, inner, bit_mask);
	else
		DR_STE_SET_MPLS_MASK(mpls, misc2_mask, outer, bit_mask);
}