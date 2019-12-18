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
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp {struct mlxsw_sp_port** ports; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 size_t MLXSW_PORT_CPU_PORT ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  mlxsw_core_cpu_port_fini (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_cpu_port_remove(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_port *mlxsw_sp_port =
				mlxsw_sp->ports[MLXSW_PORT_CPU_PORT];

	mlxsw_core_cpu_port_fini(mlxsw_sp->core);
	mlxsw_sp->ports[MLXSW_PORT_CPU_PORT] = NULL;
	kfree(mlxsw_sp_port);
}