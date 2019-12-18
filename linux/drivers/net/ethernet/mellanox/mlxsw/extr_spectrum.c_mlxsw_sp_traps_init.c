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
struct mlxsw_sp {int /*<<< orphan*/  listeners_count; int /*<<< orphan*/  listeners; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_cpu_policers_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_listener ; 
 int mlxsw_sp_trap_groups_set (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_traps_register (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_traps_unregister (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_traps_init(struct mlxsw_sp *mlxsw_sp)
{
	int err;

	err = mlxsw_sp_cpu_policers_set(mlxsw_sp->core);
	if (err)
		return err;

	err = mlxsw_sp_trap_groups_set(mlxsw_sp->core);
	if (err)
		return err;

	err = mlxsw_sp_traps_register(mlxsw_sp, mlxsw_sp_listener,
				      ARRAY_SIZE(mlxsw_sp_listener));
	if (err)
		return err;

	err = mlxsw_sp_traps_register(mlxsw_sp, mlxsw_sp->listeners,
				      mlxsw_sp->listeners_count);
	if (err)
		goto err_extra_traps_init;

	return 0;

err_extra_traps_init:
	mlxsw_sp_traps_unregister(mlxsw_sp, mlxsw_sp_listener,
				  ARRAY_SIZE(mlxsw_sp_listener));
	return err;
}