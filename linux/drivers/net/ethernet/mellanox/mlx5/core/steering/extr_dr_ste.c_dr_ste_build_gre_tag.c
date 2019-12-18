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
struct mlx5dr_match_misc {int dummy; } ;
struct mlx5dr_match_param {struct mlx5dr_match_misc misc; } ;
struct dr_hw_ste_format {int /*<<< orphan*/ * tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SET_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5dr_match_misc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gre ; 
 int /*<<< orphan*/  gre_c_present ; 
 int /*<<< orphan*/  gre_k_present ; 
 int /*<<< orphan*/  gre_key_h ; 
 int /*<<< orphan*/  gre_key_l ; 
 int /*<<< orphan*/  gre_protocol ; 
 int /*<<< orphan*/  gre_s_present ; 

__attribute__((used)) static int dr_ste_build_gre_tag(struct mlx5dr_match_param *value,
				struct mlx5dr_ste_build *sb,
				u8 *hw_ste_p)
{
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)hw_ste_p;
	struct  mlx5dr_match_misc *misc = &value->misc;
	u8 *tag = hw_ste->tag;

	DR_STE_SET_TAG(gre, tag, gre_protocol, misc, gre_protocol);

	DR_STE_SET_TAG(gre, tag, gre_k_present, misc, gre_k_present);
	DR_STE_SET_TAG(gre, tag, gre_key_h, misc, gre_key_h);
	DR_STE_SET_TAG(gre, tag, gre_key_l, misc, gre_key_l);

	DR_STE_SET_TAG(gre, tag, gre_c_present, misc, gre_c_present);

	DR_STE_SET_TAG(gre, tag, gre_s_present, misc, gre_s_present);

	return 0;
}