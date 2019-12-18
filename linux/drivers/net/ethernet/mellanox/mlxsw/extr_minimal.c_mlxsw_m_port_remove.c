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
typedef  size_t u8 ;
struct mlxsw_m_port {int /*<<< orphan*/  dev; } ;
struct mlxsw_m {int /*<<< orphan*/  core; struct mlxsw_m_port** ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_port_clear (int /*<<< orphan*/ ,size_t,struct mlxsw_m*) ; 
 int /*<<< orphan*/  mlxsw_core_port_fini (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_m_port_remove(struct mlxsw_m *mlxsw_m, u8 local_port)
{
	struct mlxsw_m_port *mlxsw_m_port = mlxsw_m->ports[local_port];

	mlxsw_core_port_clear(mlxsw_m->core, local_port, mlxsw_m);
	unregister_netdev(mlxsw_m_port->dev); /* This calls ndo_stop */
	mlxsw_m->ports[local_port] = NULL;
	free_netdev(mlxsw_m_port->dev);
	mlxsw_core_port_fini(mlxsw_m->core, local_port);
}