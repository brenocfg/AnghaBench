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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_sb_pool_des {int /*<<< orphan*/  pool; } ;
struct mlxsw_sp_sb_mm {size_t pool_index; int /*<<< orphan*/  max_buff; int /*<<< orphan*/  min_buff; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; TYPE_1__* sb_vals; } ;
struct TYPE_2__ {int mms_count; struct mlxsw_sp_sb_pool_des* pool_dess; struct mlxsw_sp_sb_mm* mms; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SBMM_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sbmm_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_bytes_cells (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbmm ; 

__attribute__((used)) static int mlxsw_sp_sb_mms_init(struct mlxsw_sp *mlxsw_sp)
{
	char sbmm_pl[MLXSW_REG_SBMM_LEN];
	int i;
	int err;

	for (i = 0; i < mlxsw_sp->sb_vals->mms_count; i++) {
		const struct mlxsw_sp_sb_pool_des *des;
		const struct mlxsw_sp_sb_mm *mc;
		u32 min_buff;

		mc = &mlxsw_sp->sb_vals->mms[i];
		des = &mlxsw_sp->sb_vals->pool_dess[mc->pool_index];
		/* All pools used by sb_mm's are initialized using dynamic
		 * thresholds, therefore 'max_buff' isn't specified in cells.
		 */
		min_buff = mlxsw_sp_bytes_cells(mlxsw_sp, mc->min_buff);
		mlxsw_reg_sbmm_pack(sbmm_pl, i, min_buff, mc->max_buff,
				    des->pool);
		err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sbmm), sbmm_pl);
		if (err)
			return err;
	}
	return 0;
}