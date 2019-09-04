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
typedef  void* u32 ;
struct mlxsw_sp_sb_cm {int /*<<< orphan*/  pool; void* max_buff; void* min_buff; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SBCM_LEN ; 
 int /*<<< orphan*/  MLXSW_SP_SB_TC_COUNT ; 
 int /*<<< orphan*/  mlxsw_reg_sbcm_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,void*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_sp_sb_cm* mlxsw_sp_sb_cm_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sbcm ; 

__attribute__((used)) static int mlxsw_sp_sb_cm_write(struct mlxsw_sp *mlxsw_sp, u8 local_port,
				u8 pg_buff, enum mlxsw_reg_sbxx_dir dir,
				u32 min_buff, u32 max_buff, u8 pool)
{
	char sbcm_pl[MLXSW_REG_SBCM_LEN];
	int err;

	mlxsw_reg_sbcm_pack(sbcm_pl, local_port, pg_buff, dir,
			    min_buff, max_buff, pool);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sbcm), sbcm_pl);
	if (err)
		return err;
	if (pg_buff < MLXSW_SP_SB_TC_COUNT) {
		struct mlxsw_sp_sb_cm *cm;

		cm = mlxsw_sp_sb_cm_get(mlxsw_sp, local_port, pg_buff, dir);
		cm->min_buff = min_buff;
		cm->max_buff = max_buff;
		cm->pool = pool;
	}
	return 0;
}