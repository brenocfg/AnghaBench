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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
typedef  size_t u16 ;
struct mlxsw_sp_sb_pool_des {int /*<<< orphan*/  dir; int /*<<< orphan*/  pool; } ;
struct mlxsw_sp_sb_cm {size_t pool_index; void* max_buff; void* min_buff; } ;
struct mlxsw_sp {TYPE_2__* sb; int /*<<< orphan*/  core; TYPE_1__* sb_vals; } ;
struct TYPE_4__ {int /*<<< orphan*/  sb_size; } ;
struct TYPE_3__ {struct mlxsw_sp_sb_pool_des* pool_dess; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SBCM_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sbcm_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* mlxsw_sp_bytes_cells (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_sp_sb_cm_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_sb_cm* mlxsw_sp_sb_cm_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbcm ; 

__attribute__((used)) static int mlxsw_sp_sb_cm_write(struct mlxsw_sp *mlxsw_sp, u8 local_port,
				u8 pg_buff, u32 min_buff, u32 max_buff,
				bool infi_max, u16 pool_index)
{
	const struct mlxsw_sp_sb_pool_des *des =
		&mlxsw_sp->sb_vals->pool_dess[pool_index];
	char sbcm_pl[MLXSW_REG_SBCM_LEN];
	struct mlxsw_sp_sb_cm *cm;
	int err;

	mlxsw_reg_sbcm_pack(sbcm_pl, local_port, pg_buff, des->dir,
			    min_buff, max_buff, infi_max, des->pool);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sbcm), sbcm_pl);
	if (err)
		return err;

	if (mlxsw_sp_sb_cm_exists(pg_buff, des->dir)) {
		if (infi_max)
			max_buff = mlxsw_sp_bytes_cells(mlxsw_sp,
							mlxsw_sp->sb->sb_size);

		cm = mlxsw_sp_sb_cm_get(mlxsw_sp, local_port, pg_buff,
					des->dir);
		cm->min_buff = min_buff;
		cm->max_buff = max_buff;
		cm->pool_index = pool_index;
	}
	return 0;
}