#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct mlxsw_sp_sb_pr {int mode; int /*<<< orphan*/  size; } ;
struct mlxsw_sp_sb_pool_des {int /*<<< orphan*/  dir; int /*<<< orphan*/  pool; } ;
struct mlxsw_sp {TYPE_1__* sb; int /*<<< orphan*/  core; TYPE_2__* sb_vals; } ;
typedef  enum mlxsw_reg_sbpr_mode { ____Placeholder_mlxsw_reg_sbpr_mode } mlxsw_reg_sbpr_mode ;
struct TYPE_4__ {struct mlxsw_sp_sb_pool_des* pool_dess; } ;
struct TYPE_3__ {int /*<<< orphan*/  sb_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SBPR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sbpr_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_bytes_cells (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_sb_pr* mlxsw_sp_sb_pr_get (struct mlxsw_sp*,size_t) ; 
 int /*<<< orphan*/  sbpr ; 

__attribute__((used)) static int mlxsw_sp_sb_pr_write(struct mlxsw_sp *mlxsw_sp, u16 pool_index,
				enum mlxsw_reg_sbpr_mode mode,
				u32 size, bool infi_size)
{
	const struct mlxsw_sp_sb_pool_des *des =
		&mlxsw_sp->sb_vals->pool_dess[pool_index];
	char sbpr_pl[MLXSW_REG_SBPR_LEN];
	struct mlxsw_sp_sb_pr *pr;
	int err;

	mlxsw_reg_sbpr_pack(sbpr_pl, des->pool, des->dir, mode,
			    size, infi_size);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sbpr), sbpr_pl);
	if (err)
		return err;

	if (infi_size)
		size = mlxsw_sp_bytes_cells(mlxsw_sp, mlxsw_sp->sb->sb_size);
	pr = mlxsw_sp_sb_pr_get(mlxsw_sp, pool_index);
	pr->mode = mode;
	pr->size = size;
	return 0;
}