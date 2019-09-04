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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_sb_pr {scalar_t__ mode; int /*<<< orphan*/  size; } ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_core {int dummy; } ;
struct devlink_sb_pool_info {int pool_type; int threshold_type; int /*<<< orphan*/  size; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;
typedef  enum devlink_sb_threshold_type { ____Placeholder_devlink_sb_threshold_type } devlink_sb_threshold_type ;
typedef  enum devlink_sb_pool_type { ____Placeholder_devlink_sb_pool_type } devlink_sb_pool_type ;

/* Variables and functions */
 int dir_get (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_sp_cells_bytes (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_sb_pr* mlxsw_sp_sb_pr_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pool_get (int /*<<< orphan*/ ) ; 

int mlxsw_sp_sb_pool_get(struct mlxsw_core *mlxsw_core,
			 unsigned int sb_index, u16 pool_index,
			 struct devlink_sb_pool_info *pool_info)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	u8 pool = pool_get(pool_index);
	enum mlxsw_reg_sbxx_dir dir = dir_get(pool_index);
	struct mlxsw_sp_sb_pr *pr = mlxsw_sp_sb_pr_get(mlxsw_sp, pool, dir);

	pool_info->pool_type = (enum devlink_sb_pool_type) dir;
	pool_info->size = mlxsw_sp_cells_bytes(mlxsw_sp, pr->size);
	pool_info->threshold_type = (enum devlink_sb_threshold_type) pr->mode;
	return 0;
}