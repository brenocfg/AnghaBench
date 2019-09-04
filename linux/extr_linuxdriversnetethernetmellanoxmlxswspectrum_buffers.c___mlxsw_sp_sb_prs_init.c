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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_sb_pr {int /*<<< orphan*/  mode; int /*<<< orphan*/  size; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_bytes_cells (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_sb_pr_write (struct mlxsw_sp*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __mlxsw_sp_sb_prs_init(struct mlxsw_sp *mlxsw_sp,
				  enum mlxsw_reg_sbxx_dir dir,
				  const struct mlxsw_sp_sb_pr *prs,
				  size_t prs_len)
{
	int i;
	int err;

	for (i = 0; i < prs_len; i++) {
		u32 size = mlxsw_sp_bytes_cells(mlxsw_sp, prs[i].size);

		err = mlxsw_sp_sb_pr_write(mlxsw_sp, i, dir, prs[i].mode, size);
		if (err)
			return err;
	}
	return 0;
}