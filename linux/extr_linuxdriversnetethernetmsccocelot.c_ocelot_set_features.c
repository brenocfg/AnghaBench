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
struct ocelot_port {int dummy; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ocelot_vlan_mode (struct ocelot_port*,int) ; 

__attribute__((used)) static int ocelot_set_features(struct net_device *dev,
			       netdev_features_t features)
{
	struct ocelot_port *port = netdev_priv(dev);
	netdev_features_t changed = dev->features ^ features;

	if (changed & NETIF_F_HW_VLAN_CTAG_FILTER)
		ocelot_vlan_mode(port, features);

	return 0;
}