#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mlxsw_sx_port {int /*<<< orphan*/  local_port; TYPE_1__* mlxsw_sx; } ;
struct TYPE_2__ {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int mlxsw_core_port_get_phys_port_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 struct mlxsw_sx_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sx_port_get_phys_port_name(struct net_device *dev, char *name,
					    size_t len)
{
	struct mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);

	return mlxsw_core_port_get_phys_port_name(mlxsw_sx_port->mlxsw_sx->core,
						  mlxsw_sx_port->local_port,
						  name, len);
}