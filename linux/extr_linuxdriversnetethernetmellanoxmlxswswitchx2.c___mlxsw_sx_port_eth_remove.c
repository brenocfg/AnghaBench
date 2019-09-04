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
struct mlxsw_sx_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  pcpu_stats; } ;
struct mlxsw_sx {struct mlxsw_sx_port** ports; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_PORT_SWID_DISABLED_PORT ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_port_clear (int /*<<< orphan*/ ,size_t,struct mlxsw_sx*) ; 
 int /*<<< orphan*/  mlxsw_sx_port_swid_set (struct mlxsw_sx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mlxsw_sx_port_eth_remove(struct mlxsw_sx *mlxsw_sx, u8 local_port)
{
	struct mlxsw_sx_port *mlxsw_sx_port = mlxsw_sx->ports[local_port];

	mlxsw_core_port_clear(mlxsw_sx->core, local_port, mlxsw_sx);
	unregister_netdev(mlxsw_sx_port->dev); /* This calls ndo_stop */
	mlxsw_sx->ports[local_port] = NULL;
	mlxsw_sx_port_swid_set(mlxsw_sx_port, MLXSW_PORT_SWID_DISABLED_PORT);
	free_percpu(mlxsw_sx_port->pcpu_stats);
	free_netdev(mlxsw_sx_port->dev);
}