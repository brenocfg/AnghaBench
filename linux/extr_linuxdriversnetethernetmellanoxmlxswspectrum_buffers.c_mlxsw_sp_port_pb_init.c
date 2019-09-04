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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PBMC_LEN ; 
 int MLXSW_REG_PBMC_PORT_SHARED_BUF_IDX ; 
 int MLXSW_SP_PBS_LEN ; 
 int MLXSW_SP_PB_UNUSED ; 
 int /*<<< orphan*/  mlxsw_reg_pbmc_lossy_buffer_pack (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pbmc_pack (char*,int /*<<< orphan*/ ,int,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_bytes_cells (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlxsw_sp_pbs ; 
 int /*<<< orphan*/  pbmc ; 

__attribute__((used)) static int mlxsw_sp_port_pb_init(struct mlxsw_sp_port *mlxsw_sp_port)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char pbmc_pl[MLXSW_REG_PBMC_LEN];
	int i;

	mlxsw_reg_pbmc_pack(pbmc_pl, mlxsw_sp_port->local_port,
			    0xffff, 0xffff / 2);
	for (i = 0; i < MLXSW_SP_PBS_LEN; i++) {
		u16 size = mlxsw_sp_bytes_cells(mlxsw_sp, mlxsw_sp_pbs[i]);

		if (i == MLXSW_SP_PB_UNUSED)
			continue;
		mlxsw_reg_pbmc_lossy_buffer_pack(pbmc_pl, i, size);
	}
	mlxsw_reg_pbmc_lossy_buffer_pack(pbmc_pl,
					 MLXSW_REG_PBMC_PORT_SHARED_BUF_IDX, 0);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(pbmc), pbmc_pl);
}