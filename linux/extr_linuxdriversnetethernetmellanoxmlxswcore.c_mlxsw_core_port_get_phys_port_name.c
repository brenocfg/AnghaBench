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
struct devlink_port {int dummy; } ;
struct mlxsw_core_port {struct devlink_port devlink_port; } ;
struct mlxsw_core {struct mlxsw_core_port* ports; } ;

/* Variables and functions */
 int devlink_port_get_phys_port_name (struct devlink_port*,char*,size_t) ; 

int mlxsw_core_port_get_phys_port_name(struct mlxsw_core *mlxsw_core,
				       u8 local_port, char *name, size_t len)
{
	struct mlxsw_core_port *mlxsw_core_port =
					&mlxsw_core->ports[local_port];
	struct devlink_port *devlink_port = &mlxsw_core_port->devlink_port;

	return devlink_port_get_phys_port_name(devlink_port, name, len);
}