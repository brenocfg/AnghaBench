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
struct mlx5dr_ste_build {scalar_t__ inner; } ;
struct mlx5dr_match_misc2 {int dummy; } ;
struct mlx5dr_match_param {struct mlx5dr_match_misc2 misc2; } ;
struct dr_hw_ste_format {int /*<<< orphan*/ * tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SET_MPLS_TAG (int /*<<< orphan*/ ,struct mlx5dr_match_misc2*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inner ; 
 int /*<<< orphan*/  mpls ; 
 int /*<<< orphan*/  outer ; 

__attribute__((used)) static int dr_ste_build_mpls_tag(struct mlx5dr_match_param *value,
				 struct mlx5dr_ste_build *sb,
				 u8 *hw_ste_p)
{
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)hw_ste_p;
	struct mlx5dr_match_misc2 *misc2_mask = &value->misc2;
	u8 *tag = hw_ste->tag;

	if (sb->inner)
		DR_STE_SET_MPLS_TAG(mpls, misc2_mask, inner, tag);
	else
		DR_STE_SET_MPLS_TAG(mpls, misc2_mask, outer, tag);

	return 0;
}