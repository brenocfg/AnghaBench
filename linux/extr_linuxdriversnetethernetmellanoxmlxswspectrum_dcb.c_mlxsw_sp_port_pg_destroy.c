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
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PBMC_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_pbmc_lossy_buffer_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pbmc_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_ets_has_pg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbmc ; 

__attribute__((used)) static int mlxsw_sp_port_pg_destroy(struct mlxsw_sp_port *mlxsw_sp_port,
				    u8 *old_prio_tc, u8 *new_prio_tc)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char pbmc_pl[MLXSW_REG_PBMC_LEN];
	int err, i;

	mlxsw_reg_pbmc_pack(pbmc_pl, mlxsw_sp_port->local_port, 0, 0);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(pbmc), pbmc_pl);
	if (err)
		return err;

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		u8 pg = old_prio_tc[i];

		if (!mlxsw_sp_ets_has_pg(new_prio_tc, pg))
			mlxsw_reg_pbmc_lossy_buffer_pack(pbmc_pl, pg, 0);
	}

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(pbmc), pbmc_pl);
}