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
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_core {unsigned int max_ports; TYPE_1__* driver; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int (* port_unsplit ) (struct mlxsw_core*,unsigned int,struct netlink_ext_ack*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 struct mlxsw_core* devlink_priv (struct devlink*) ; 
 int stub1 (struct mlxsw_core*,unsigned int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int mlxsw_devlink_port_unsplit(struct devlink *devlink,
				      unsigned int port_index,
				      struct netlink_ext_ack *extack)
{
	struct mlxsw_core *mlxsw_core = devlink_priv(devlink);

	if (port_index >= mlxsw_core->max_ports) {
		NL_SET_ERR_MSG_MOD(extack, "Port index exceeds maximum number of ports");
		return -EINVAL;
	}
	if (!mlxsw_core->driver->port_unsplit)
		return -EOPNOTSUPP;
	return mlxsw_core->driver->port_unsplit(mlxsw_core, port_index,
						extack);
}