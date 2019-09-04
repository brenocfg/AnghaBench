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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_sb_pr {int mode; int /*<<< orphan*/  size; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;
typedef  enum mlxsw_reg_sbpr_mode { ____Placeholder_mlxsw_reg_sbpr_mode } mlxsw_reg_sbpr_mode ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SBPR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sbpr_pack (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_sp_sb_pr* mlxsw_sp_sb_pr_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sbpr ; 

__attribute__((used)) static int mlxsw_sp_sb_pr_write(struct mlxsw_sp *mlxsw_sp, u8 pool,
				enum mlxsw_reg_sbxx_dir dir,
				enum mlxsw_reg_sbpr_mode mode, u32 size)
{
	char sbpr_pl[MLXSW_REG_SBPR_LEN];
	struct mlxsw_sp_sb_pr *pr;
	int err;

	mlxsw_reg_sbpr_pack(sbpr_pl, pool, dir, mode, size);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sbpr), sbpr_pl);
	if (err)
		return err;

	pr = mlxsw_sp_sb_pr_get(mlxsw_sp, pool, dir);
	pr->mode = mode;
	pr->size = size;
	return 0;
}