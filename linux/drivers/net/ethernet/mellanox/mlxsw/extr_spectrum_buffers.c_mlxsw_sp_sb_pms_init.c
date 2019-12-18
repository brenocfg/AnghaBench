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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_sb_pool_des {scalar_t__ dir; } ;
struct mlxsw_sp_sb_pm {int /*<<< orphan*/  max_buff; int /*<<< orphan*/  min_buff; } ;
struct mlxsw_sp {TYPE_1__* sb_vals; } ;
struct TYPE_2__ {int pool_count; struct mlxsw_sp_sb_pool_des* pool_dess; } ;

/* Variables and functions */
 scalar_t__ MLXSW_REG_SBXX_DIR_INGRESS ; 
 int /*<<< orphan*/  mlxsw_sp_bytes_cells (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_sb_pm_write (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_sp_sb_pool_is_static (struct mlxsw_sp*,int) ; 

__attribute__((used)) static int mlxsw_sp_sb_pms_init(struct mlxsw_sp *mlxsw_sp, u8 local_port,
				const struct mlxsw_sp_sb_pm *pms,
				bool skip_ingress)
{
	int i, err;

	for (i = 0; i < mlxsw_sp->sb_vals->pool_count; i++) {
		const struct mlxsw_sp_sb_pm *pm = &pms[i];
		const struct mlxsw_sp_sb_pool_des *des;
		u32 max_buff;
		u32 min_buff;

		des = &mlxsw_sp->sb_vals->pool_dess[i];
		if (skip_ingress && des->dir == MLXSW_REG_SBXX_DIR_INGRESS)
			continue;

		min_buff = mlxsw_sp_bytes_cells(mlxsw_sp, pm->min_buff);
		max_buff = pm->max_buff;
		if (mlxsw_sp_sb_pool_is_static(mlxsw_sp, i))
			max_buff = mlxsw_sp_bytes_cells(mlxsw_sp, max_buff);
		err = mlxsw_sp_sb_pm_write(mlxsw_sp, local_port, i, min_buff,
					   max_buff);
		if (err)
			return err;
	}
	return 0;
}