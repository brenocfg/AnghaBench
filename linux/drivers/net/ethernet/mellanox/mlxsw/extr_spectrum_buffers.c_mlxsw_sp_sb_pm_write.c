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
typedef  void* u32 ;
typedef  size_t u16 ;
struct mlxsw_sp_sb_pool_des {int /*<<< orphan*/  dir; int /*<<< orphan*/  pool; } ;
struct mlxsw_sp_sb_pm {void* max_buff; void* min_buff; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; TYPE_1__* sb_vals; } ;
struct TYPE_2__ {struct mlxsw_sp_sb_pool_des* pool_dess; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SBPM_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sbpm_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,void*) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_sp_sb_pm* mlxsw_sp_sb_pm_get (struct mlxsw_sp*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sbpm ; 

__attribute__((used)) static int mlxsw_sp_sb_pm_write(struct mlxsw_sp *mlxsw_sp, u8 local_port,
				u16 pool_index, u32 min_buff, u32 max_buff)
{
	const struct mlxsw_sp_sb_pool_des *des =
		&mlxsw_sp->sb_vals->pool_dess[pool_index];
	char sbpm_pl[MLXSW_REG_SBPM_LEN];
	struct mlxsw_sp_sb_pm *pm;
	int err;

	mlxsw_reg_sbpm_pack(sbpm_pl, local_port, des->pool, des->dir, false,
			    min_buff, max_buff);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sbpm), sbpm_pl);
	if (err)
		return err;

	pm = mlxsw_sp_sb_pm_get(mlxsw_sp, local_port, pool_index);
	pm->min_buff = min_buff;
	pm->max_buff = max_buff;
	return 0;
}