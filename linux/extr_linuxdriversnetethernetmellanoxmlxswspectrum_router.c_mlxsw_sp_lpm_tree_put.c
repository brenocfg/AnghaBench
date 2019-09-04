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
struct mlxsw_sp_lpm_tree {scalar_t__ ref_count; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_lpm_tree_destroy (struct mlxsw_sp*,struct mlxsw_sp_lpm_tree*) ; 

__attribute__((used)) static void mlxsw_sp_lpm_tree_put(struct mlxsw_sp *mlxsw_sp,
				  struct mlxsw_sp_lpm_tree *lpm_tree)
{
	if (--lpm_tree->ref_count == 0)
		mlxsw_sp_lpm_tree_destroy(mlxsw_sp, lpm_tree);
}