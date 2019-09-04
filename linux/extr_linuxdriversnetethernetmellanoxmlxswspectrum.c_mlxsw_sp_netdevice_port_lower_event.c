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
struct netdev_notifier_changelowerstate_info {int /*<<< orphan*/  lower_state_info; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  lagged; } ;

/* Variables and functions */
#define  NETDEV_CHANGELOWERSTATE 128 
 int mlxsw_sp_port_lag_changed (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_lag_port (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_netdevice_port_lower_event(struct net_device *dev,
					       unsigned long event, void *ptr)
{
	struct netdev_notifier_changelowerstate_info *info;
	struct mlxsw_sp_port *mlxsw_sp_port;
	int err;

	mlxsw_sp_port = netdev_priv(dev);
	info = ptr;

	switch (event) {
	case NETDEV_CHANGELOWERSTATE:
		if (netif_is_lag_port(dev) && mlxsw_sp_port->lagged) {
			err = mlxsw_sp_port_lag_changed(mlxsw_sp_port,
							info->lower_state_info);
			if (err)
				netdev_err(dev, "Failed to reflect link aggregation lower state change\n");
		}
		break;
	}

	return 0;
}