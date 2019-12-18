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
struct mlx5dr_match_misc2 {scalar_t__ metadata_reg_c_7; scalar_t__ metadata_reg_c_6; scalar_t__ metadata_reg_c_5; scalar_t__ metadata_reg_c_4; } ;

/* Variables and functions */

__attribute__((used)) static bool dr_mask_is_reg_c_4_7_set(struct mlx5dr_match_misc2 *misc2)
{
	return (misc2->metadata_reg_c_4 || misc2->metadata_reg_c_5 ||
		misc2->metadata_reg_c_6 || misc2->metadata_reg_c_7);
}