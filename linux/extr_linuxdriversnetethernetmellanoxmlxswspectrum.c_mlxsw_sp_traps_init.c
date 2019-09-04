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
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int mlxsw_core_trap_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_core_trap_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_sp*) ; 
 int mlxsw_sp_cpu_policers_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlxsw_sp_listener ; 
 int mlxsw_sp_trap_groups_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_traps_init(struct mlxsw_sp *mlxsw_sp)
{
	int i;
	int err;

	err = mlxsw_sp_cpu_policers_set(mlxsw_sp->core);
	if (err)
		return err;

	err = mlxsw_sp_trap_groups_set(mlxsw_sp->core);
	if (err)
		return err;

	for (i = 0; i < ARRAY_SIZE(mlxsw_sp_listener); i++) {
		err = mlxsw_core_trap_register(mlxsw_sp->core,
					       &mlxsw_sp_listener[i],
					       mlxsw_sp);
		if (err)
			goto err_listener_register;

	}
	return 0;

err_listener_register:
	for (i--; i >= 0; i--) {
		mlxsw_core_trap_unregister(mlxsw_sp->core,
					   &mlxsw_sp_listener[i],
					   mlxsw_sp);
	}
	return err;
}