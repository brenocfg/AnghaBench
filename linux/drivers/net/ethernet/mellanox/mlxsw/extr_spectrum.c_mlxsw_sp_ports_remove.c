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
struct mlxsw_sp {int /*<<< orphan*/  ports; int /*<<< orphan*/  port_to_module; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int mlxsw_core_max_ports (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_cpu_port_remove (struct mlxsw_sp*) ; 
 scalar_t__ mlxsw_sp_port_created (struct mlxsw_sp*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_remove (struct mlxsw_sp*,int) ; 

__attribute__((used)) static void mlxsw_sp_ports_remove(struct mlxsw_sp *mlxsw_sp)
{
	int i;

	for (i = 1; i < mlxsw_core_max_ports(mlxsw_sp->core); i++)
		if (mlxsw_sp_port_created(mlxsw_sp, i))
			mlxsw_sp_port_remove(mlxsw_sp, i);
	mlxsw_sp_cpu_port_remove(mlxsw_sp);
	kfree(mlxsw_sp->port_to_module);
	kfree(mlxsw_sp->ports);
}