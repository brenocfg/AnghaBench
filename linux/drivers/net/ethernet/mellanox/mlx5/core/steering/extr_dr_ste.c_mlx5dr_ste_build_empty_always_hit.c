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
struct mlx5dr_ste_build {int rx; int /*<<< orphan*/ * ste_build_tag_func; scalar_t__ byte_mask; int /*<<< orphan*/  lu_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5DR_STE_LU_TYPE_DONT_CARE ; 
 int /*<<< orphan*/  dr_ste_build_empty_always_hit_tag ; 

void mlx5dr_ste_build_empty_always_hit(struct mlx5dr_ste_build *sb, bool rx)
{
	sb->rx = rx;
	sb->lu_type = MLX5DR_STE_LU_TYPE_DONT_CARE;
	sb->byte_mask = 0;
	sb->ste_build_tag_func = &dr_ste_build_empty_always_hit_tag;
}