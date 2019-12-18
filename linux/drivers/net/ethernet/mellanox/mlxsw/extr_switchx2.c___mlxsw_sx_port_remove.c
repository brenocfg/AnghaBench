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
struct mlxsw_sx {int /*<<< orphan*/  core; } ;
typedef  enum devlink_port_type { ____Placeholder_devlink_port_type } devlink_port_type ;

/* Variables and functions */
 int DEVLINK_PORT_TYPE_ETH ; 
 int DEVLINK_PORT_TYPE_IB ; 
 int /*<<< orphan*/  __mlxsw_sx_port_eth_remove (struct mlxsw_sx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mlxsw_sx_port_ib_remove (struct mlxsw_sx*,int /*<<< orphan*/ ) ; 
 int mlxsw_core_port_type_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mlxsw_sx_port_remove(struct mlxsw_sx *mlxsw_sx, u8 local_port)
{
	enum devlink_port_type port_type =
		mlxsw_core_port_type_get(mlxsw_sx->core, local_port);

	if (port_type == DEVLINK_PORT_TYPE_ETH)
		__mlxsw_sx_port_eth_remove(mlxsw_sx, local_port);
	else if (port_type == DEVLINK_PORT_TYPE_IB)
		__mlxsw_sx_port_ib_remove(mlxsw_sx, local_port);
}