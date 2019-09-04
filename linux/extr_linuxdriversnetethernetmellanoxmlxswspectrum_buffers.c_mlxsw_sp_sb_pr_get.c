#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct mlxsw_sp_sb_pr {int dummy; } ;
struct mlxsw_sp {TYPE_1__* sb; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;
struct TYPE_2__ {struct mlxsw_sp_sb_pr** prs; } ;

/* Variables and functions */

__attribute__((used)) static struct mlxsw_sp_sb_pr *mlxsw_sp_sb_pr_get(struct mlxsw_sp *mlxsw_sp,
						 u8 pool,
						 enum mlxsw_reg_sbxx_dir dir)
{
	return &mlxsw_sp->sb->prs[dir][pool];
}