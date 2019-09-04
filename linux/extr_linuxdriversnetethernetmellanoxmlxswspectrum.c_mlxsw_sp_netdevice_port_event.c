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
struct net_device {int dummy; } ;

/* Variables and functions */
#define  NETDEV_CHANGELOWERSTATE 130 
#define  NETDEV_CHANGEUPPER 129 
#define  NETDEV_PRECHANGEUPPER 128 
 int mlxsw_sp_netdevice_port_lower_event (struct net_device*,unsigned long,void*) ; 
 int mlxsw_sp_netdevice_port_upper_event (struct net_device*,struct net_device*,unsigned long,void*) ; 

__attribute__((used)) static int mlxsw_sp_netdevice_port_event(struct net_device *lower_dev,
					 struct net_device *port_dev,
					 unsigned long event, void *ptr)
{
	switch (event) {
	case NETDEV_PRECHANGEUPPER:
	case NETDEV_CHANGEUPPER:
		return mlxsw_sp_netdevice_port_upper_event(lower_dev, port_dev,
							   event, ptr);
	case NETDEV_CHANGELOWERSTATE:
		return mlxsw_sp_netdevice_port_lower_event(port_dev, event,
							   ptr);
	}

	return 0;
}