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
struct qlcnic_adapter {int flags; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_LRO ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int QLCNIC_APP_CHANGED_FLAGS ; 
 int QLCNIC_ESWITCH_ENABLED ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_process_flags (struct qlcnic_adapter*,int) ; 

netdev_features_t qlcnic_fix_features(struct net_device *netdev,
	netdev_features_t features)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	netdev_features_t changed;

	if (qlcnic_82xx_check(adapter) &&
	    (adapter->flags & QLCNIC_ESWITCH_ENABLED)) {
		if (adapter->flags & QLCNIC_APP_CHANGED_FLAGS) {
			features = qlcnic_process_flags(adapter, features);
		} else {
			changed = features ^ netdev->features;
			features ^= changed & (NETIF_F_RXCSUM |
					       NETIF_F_IP_CSUM |
					       NETIF_F_IPV6_CSUM |
					       NETIF_F_TSO |
					       NETIF_F_TSO6);
		}
	}

	if (!(features & NETIF_F_RXCSUM))
		features &= ~NETIF_F_LRO;

	return features;
}