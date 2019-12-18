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
 int /*<<< orphan*/  DR_STE_SET_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5dr_match_misc2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_reg_c_0 ; 
 int /*<<< orphan*/  metadata_reg_c_1 ; 
 int /*<<< orphan*/  metadata_reg_c_2 ; 
 int /*<<< orphan*/  metadata_reg_c_3 ; 
 int /*<<< orphan*/  register_0 ; 
 int /*<<< orphan*/  register_0_h ; 
 int /*<<< orphan*/  register_0_l ; 
 int /*<<< orphan*/  register_1_h ; 
 int /*<<< orphan*/  register_1_l ; 

__attribute__((used)) static int dr_ste_build_register_0_tag(struct mlx5dr_match_param *value,
				       struct mlx5dr_ste_build *sb,
				       u8 *hw_ste_p)
{
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)hw_ste_p;
	struct mlx5dr_match_misc2 *misc2 = &value->misc2;
	u8 *tag = hw_ste->tag;

	DR_STE_SET_TAG(register_0, tag, register_0_h, misc2, metadata_reg_c_0);
	DR_STE_SET_TAG(register_0, tag, register_0_l, misc2, metadata_reg_c_1);
	DR_STE_SET_TAG(register_0, tag, register_1_h, misc2, metadata_reg_c_2);
	DR_STE_SET_TAG(register_0, tag, register_1_l, misc2, metadata_reg_c_3);

	return 0;
}