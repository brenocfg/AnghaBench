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
struct TYPE_2__ {scalar_t__ offload_cnt; } ;
struct ocelot_port {TYPE_1__ tc; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int EBUSY ; 
 int NETIF_F_HW_TC ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ocelot_vlan_mode (struct ocelot_port*,int) ; 

__attribute__((used)) static int ocelot_set_features(struct net_device *dev,
			       netdev_features_t features)
{
	struct ocelot_port *port = netdev_priv(dev);
	netdev_features_t changed = dev->features ^ features;

	if ((dev->features & NETIF_F_HW_TC) > (features & NETIF_F_HW_TC) &&
	    port->tc.offload_cnt) {
		netdev_err(dev,
			   "Cannot disable HW TC offload while offloads active\n");
		return -EBUSY;
	}

	if (changed & NETIF_F_HW_VLAN_CTAG_FILTER)
		ocelot_vlan_mode(port, features);

	return 0;
}