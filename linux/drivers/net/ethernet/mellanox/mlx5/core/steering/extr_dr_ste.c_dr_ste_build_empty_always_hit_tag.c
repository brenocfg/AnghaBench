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
struct mlx5dr_match_param {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int dr_ste_build_empty_always_hit_tag(struct mlx5dr_match_param *value,
					     struct mlx5dr_ste_build *sb,
					     u8 *hw_ste_p)
{
	return 0;
}