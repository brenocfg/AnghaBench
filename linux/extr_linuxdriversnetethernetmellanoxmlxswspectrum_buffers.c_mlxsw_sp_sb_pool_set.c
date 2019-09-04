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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct mlxsw_core {int dummy; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;
typedef  enum mlxsw_reg_sbpr_mode { ____Placeholder_mlxsw_reg_sbpr_mode } mlxsw_reg_sbpr_mode ;
typedef  enum devlink_sb_threshold_type { ____Placeholder_devlink_sb_threshold_type } devlink_sb_threshold_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_BUFFER_SIZE ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dir_get (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_sp_bytes_cells (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_sb_pr_write (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_get (int /*<<< orphan*/ ) ; 

int mlxsw_sp_sb_pool_set(struct mlxsw_core *mlxsw_core,
			 unsigned int sb_index, u16 pool_index, u32 size,
			 enum devlink_sb_threshold_type threshold_type)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	u32 pool_size = mlxsw_sp_bytes_cells(mlxsw_sp, size);
	u8 pool = pool_get(pool_index);
	enum mlxsw_reg_sbxx_dir dir = dir_get(pool_index);
	enum mlxsw_reg_sbpr_mode mode;

	if (size > MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_BUFFER_SIZE))
		return -EINVAL;

	mode = (enum mlxsw_reg_sbpr_mode) threshold_type;
	return mlxsw_sp_sb_pr_write(mlxsw_sp, pool, dir, mode, pool_size);
}