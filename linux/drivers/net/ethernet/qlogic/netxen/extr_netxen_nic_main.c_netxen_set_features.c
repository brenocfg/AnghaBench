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
struct netxen_adapter {int dummy; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int EIO ; 
 int NETIF_F_LRO ; 
 int NETXEN_NIC_LRO_DISABLED ; 
 int NETXEN_NIC_LRO_ENABLED ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netxen_config_hw_lro (struct netxen_adapter*,int) ; 
 scalar_t__ netxen_send_lro_cleanup (struct netxen_adapter*) ; 

__attribute__((used)) static int netxen_set_features(struct net_device *dev,
	netdev_features_t features)
{
	struct netxen_adapter *adapter = netdev_priv(dev);
	int hw_lro;

	if (!((dev->features ^ features) & NETIF_F_LRO))
		return 0;

	hw_lro = (features & NETIF_F_LRO) ? NETXEN_NIC_LRO_ENABLED
	         : NETXEN_NIC_LRO_DISABLED;

	if (netxen_config_hw_lro(adapter, hw_lro))
		return -EIO;

	if (!(features & NETIF_F_LRO) && netxen_send_lro_cleanup(adapter))
		return -EIO;

	return 0;
}