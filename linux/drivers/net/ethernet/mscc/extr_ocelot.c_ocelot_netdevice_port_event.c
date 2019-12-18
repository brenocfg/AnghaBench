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
struct ocelot_port {int /*<<< orphan*/  ocelot; } ;
struct netdev_notifier_changeupper_info {int /*<<< orphan*/  upper_dev; int /*<<< orphan*/  linking; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  NETDEV_CHANGEUPPER 128 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_bridge_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_is_lag_master (int /*<<< orphan*/ ) ; 
 int ocelot_port_bridge_join (struct ocelot_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_port_bridge_leave (struct ocelot_port*,int /*<<< orphan*/ ) ; 
 int ocelot_port_lag_join (struct ocelot_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_port_lag_leave (struct ocelot_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_vlan_port_apply (int /*<<< orphan*/ ,struct ocelot_port*) ; 

__attribute__((used)) static int ocelot_netdevice_port_event(struct net_device *dev,
				       unsigned long event,
				       struct netdev_notifier_changeupper_info *info)
{
	struct ocelot_port *ocelot_port = netdev_priv(dev);
	int err = 0;

	switch (event) {
	case NETDEV_CHANGEUPPER:
		if (netif_is_bridge_master(info->upper_dev)) {
			if (info->linking)
				err = ocelot_port_bridge_join(ocelot_port,
							      info->upper_dev);
			else
				ocelot_port_bridge_leave(ocelot_port,
							 info->upper_dev);

			ocelot_vlan_port_apply(ocelot_port->ocelot,
					       ocelot_port);
		}
		if (netif_is_lag_master(info->upper_dev)) {
			if (info->linking)
				err = ocelot_port_lag_join(ocelot_port,
							   info->upper_dev);
			else
				ocelot_port_lag_leave(ocelot_port,
						      info->upper_dev);
		}
		break;
	default:
		break;
	}

	return err;
}