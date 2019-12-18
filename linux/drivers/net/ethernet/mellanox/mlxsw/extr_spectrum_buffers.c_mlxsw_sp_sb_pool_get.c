#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct mlxsw_sp_sb_pr {scalar_t__ mode; int /*<<< orphan*/  size; } ;
struct mlxsw_sp {TYPE_1__* sb; TYPE_2__* sb_vals; } ;
struct mlxsw_core {int dummy; } ;
struct devlink_sb_pool_info {int pool_type; int threshold_type; int /*<<< orphan*/  cell_size; int /*<<< orphan*/  size; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;
typedef  enum devlink_sb_threshold_type { ____Placeholder_devlink_sb_threshold_type } devlink_sb_threshold_type ;
typedef  enum devlink_sb_pool_type { ____Placeholder_devlink_sb_pool_type } devlink_sb_pool_type ;
struct TYPE_6__ {int dir; } ;
struct TYPE_5__ {TYPE_3__* pool_dess; } ;
struct TYPE_4__ {int /*<<< orphan*/  cell_size; } ;

/* Variables and functions */
 struct mlxsw_sp* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_sp_cells_bytes (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_sb_pr* mlxsw_sp_sb_pr_get (struct mlxsw_sp*,size_t) ; 

int mlxsw_sp_sb_pool_get(struct mlxsw_core *mlxsw_core,
			 unsigned int sb_index, u16 pool_index,
			 struct devlink_sb_pool_info *pool_info)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	enum mlxsw_reg_sbxx_dir dir;
	struct mlxsw_sp_sb_pr *pr;

	dir = mlxsw_sp->sb_vals->pool_dess[pool_index].dir;
	pr = mlxsw_sp_sb_pr_get(mlxsw_sp, pool_index);
	pool_info->pool_type = (enum devlink_sb_pool_type) dir;
	pool_info->size = mlxsw_sp_cells_bytes(mlxsw_sp, pr->size);
	pool_info->threshold_type = (enum devlink_sb_threshold_type) pr->mode;
	pool_info->cell_size = mlxsw_sp->sb->cell_size;
	return 0;
}