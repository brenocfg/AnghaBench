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
struct mlxsw_sp_sb_pm {int dummy; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct list_head {int dummy; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SBPM_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sbpm_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_trans_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct list_head*,int /*<<< orphan*/ ,unsigned long) ; 
 struct mlxsw_sp_sb_pm* mlxsw_sp_sb_pm_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp_sb_pm_occ_query_cb ; 
 int /*<<< orphan*/  sbpm ; 

__attribute__((used)) static int mlxsw_sp_sb_pm_occ_query(struct mlxsw_sp *mlxsw_sp, u8 local_port,
				    u8 pool, enum mlxsw_reg_sbxx_dir dir,
				    struct list_head *bulk_list)
{
	char sbpm_pl[MLXSW_REG_SBPM_LEN];
	struct mlxsw_sp_sb_pm *pm;

	pm = mlxsw_sp_sb_pm_get(mlxsw_sp, local_port, pool, dir);
	mlxsw_reg_sbpm_pack(sbpm_pl, local_port, pool, dir, false, 0, 0);
	return mlxsw_reg_trans_query(mlxsw_sp->core, MLXSW_REG(sbpm), sbpm_pl,
				     bulk_list,
				     mlxsw_sp_sb_pm_occ_query_cb,
				     (unsigned long) pm);
}