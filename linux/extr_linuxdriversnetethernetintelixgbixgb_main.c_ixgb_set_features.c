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
struct net_device {int features; } ;
struct ixgb_adapter {int rx_csum; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  ixgb_down (struct ixgb_adapter*,int) ; 
 int /*<<< orphan*/  ixgb_reset (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  ixgb_set_speed_duplex (struct net_device*) ; 
 int /*<<< orphan*/  ixgb_up (struct ixgb_adapter*) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int
ixgb_set_features(struct net_device *netdev, netdev_features_t features)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	if (!(changed & (NETIF_F_RXCSUM|NETIF_F_HW_VLAN_CTAG_RX)))
		return 0;

	adapter->rx_csum = !!(features & NETIF_F_RXCSUM);

	if (netif_running(netdev)) {
		ixgb_down(adapter, true);
		ixgb_up(adapter);
		ixgb_set_speed_duplex(netdev);
	} else
		ixgb_reset(adapter);

	return 0;
}