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
struct mlxsw_sx {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_HTGT_DEFAULT_PRIORITY ; 
 int /*<<< orphan*/  MLXSW_REG_HTGT_DEFAULT_TC ; 
 int /*<<< orphan*/  MLXSW_REG_HTGT_INVALID_POLICER ; 
 int MLXSW_REG_HTGT_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SX2_CTRL ; 
 int /*<<< orphan*/  MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SX2_RX ; 
 int /*<<< orphan*/  MLXSW_REG_HTGT_TRAP_GROUP_SX2_CTRL ; 
 int /*<<< orphan*/  MLXSW_REG_HTGT_TRAP_GROUP_SX2_RX ; 
 int /*<<< orphan*/  htgt ; 
 int mlxsw_core_trap_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_sx*) ; 
 int /*<<< orphan*/  mlxsw_core_trap_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_sx*) ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_local_path_rdq_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_htgt_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * mlxsw_sx_listener ; 

__attribute__((used)) static int mlxsw_sx_traps_init(struct mlxsw_sx *mlxsw_sx)
{
	char htgt_pl[MLXSW_REG_HTGT_LEN];
	int i;
	int err;

	mlxsw_reg_htgt_pack(htgt_pl, MLXSW_REG_HTGT_TRAP_GROUP_SX2_RX,
			    MLXSW_REG_HTGT_INVALID_POLICER,
			    MLXSW_REG_HTGT_DEFAULT_PRIORITY,
			    MLXSW_REG_HTGT_DEFAULT_TC);
	mlxsw_reg_htgt_local_path_rdq_set(htgt_pl,
					  MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SX2_RX);

	err = mlxsw_reg_write(mlxsw_sx->core, MLXSW_REG(htgt), htgt_pl);
	if (err)
		return err;

	mlxsw_reg_htgt_pack(htgt_pl, MLXSW_REG_HTGT_TRAP_GROUP_SX2_CTRL,
			    MLXSW_REG_HTGT_INVALID_POLICER,
			    MLXSW_REG_HTGT_DEFAULT_PRIORITY,
			    MLXSW_REG_HTGT_DEFAULT_TC);
	mlxsw_reg_htgt_local_path_rdq_set(htgt_pl,
					MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SX2_CTRL);

	err = mlxsw_reg_write(mlxsw_sx->core, MLXSW_REG(htgt), htgt_pl);
	if (err)
		return err;

	for (i = 0; i < ARRAY_SIZE(mlxsw_sx_listener); i++) {
		err = mlxsw_core_trap_register(mlxsw_sx->core,
					       &mlxsw_sx_listener[i],
					       mlxsw_sx);
		if (err)
			goto err_listener_register;

	}
	return 0;

err_listener_register:
	for (i--; i >= 0; i--) {
		mlxsw_core_trap_unregister(mlxsw_sx->core,
					   &mlxsw_sx_listener[i],
					   mlxsw_sx);
	}
	return err;
}