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
typedef  size_t u16 ;
struct mlxsw_sp_sb_pool_des {scalar_t__ dir; int /*<<< orphan*/  pool; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; TYPE_1__* sb_vals; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {struct mlxsw_sp_sb_pool_des* pool_dess; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_PORT_CPU_PORT ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SBPM_LEN ; 
 scalar_t__ MLXSW_REG_SBXX_DIR_INGRESS ; 
 int /*<<< orphan*/  mlxsw_reg_sbpm_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_trans_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct list_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbpm ; 

__attribute__((used)) static int mlxsw_sp_sb_pm_occ_clear(struct mlxsw_sp *mlxsw_sp, u8 local_port,
				    u16 pool_index, struct list_head *bulk_list)
{
	const struct mlxsw_sp_sb_pool_des *des =
		&mlxsw_sp->sb_vals->pool_dess[pool_index];
	char sbpm_pl[MLXSW_REG_SBPM_LEN];

	if (local_port == MLXSW_PORT_CPU_PORT &&
	    des->dir == MLXSW_REG_SBXX_DIR_INGRESS)
		return 0;

	mlxsw_reg_sbpm_pack(sbpm_pl, local_port, des->pool, des->dir,
			    true, 0, 0);
	return mlxsw_reg_trans_query(mlxsw_sp->core, MLXSW_REG(sbpm), sbpm_pl,
				     bulk_list, NULL, 0);
}