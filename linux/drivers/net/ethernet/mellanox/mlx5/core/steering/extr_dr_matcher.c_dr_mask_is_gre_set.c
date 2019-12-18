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
struct mlx5dr_match_misc {scalar_t__ gre_s_present; scalar_t__ gre_k_present; scalar_t__ gre_c_present; scalar_t__ gre_protocol; scalar_t__ gre_key_l; scalar_t__ gre_key_h; } ;

/* Variables and functions */

__attribute__((used)) static bool dr_mask_is_gre_set(struct mlx5dr_match_misc *misc)
{
	return (misc->gre_key_h || misc->gre_key_l ||
		misc->gre_protocol || misc->gre_c_present ||
		misc->gre_k_present || misc->gre_s_present);
}