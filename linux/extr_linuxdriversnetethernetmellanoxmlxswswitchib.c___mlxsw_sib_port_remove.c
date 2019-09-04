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
struct mlxsw_sib_port {int dummy; } ;
struct mlxsw_sib {struct mlxsw_sib_port** ports; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_PORT_SWID_DISABLED_PORT ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sib_port*) ; 
 int /*<<< orphan*/  mlxsw_core_port_clear (int /*<<< orphan*/ ,size_t,struct mlxsw_sib*) ; 
 int /*<<< orphan*/  mlxsw_sib_port_admin_status_set (struct mlxsw_sib_port*,int) ; 
 int /*<<< orphan*/  mlxsw_sib_port_swid_set (struct mlxsw_sib_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mlxsw_sib_port_remove(struct mlxsw_sib *mlxsw_sib, u8 local_port)
{
	struct mlxsw_sib_port *mlxsw_sib_port = mlxsw_sib->ports[local_port];

	mlxsw_core_port_clear(mlxsw_sib->core, local_port, mlxsw_sib);
	mlxsw_sib->ports[local_port] = NULL;
	mlxsw_sib_port_admin_status_set(mlxsw_sib_port, false);
	mlxsw_sib_port_swid_set(mlxsw_sib_port, MLXSW_PORT_SWID_DISABLED_PORT);
	kfree(mlxsw_sib_port);
}