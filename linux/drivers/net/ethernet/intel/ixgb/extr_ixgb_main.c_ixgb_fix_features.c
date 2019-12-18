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
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 

__attribute__((used)) static netdev_features_t
ixgb_fix_features(struct net_device *netdev, netdev_features_t features)
{
	/*
	 * Tx VLAN insertion does not work per HW design when Rx stripping is
	 * disabled.
	 */
	if (!(features & NETIF_F_HW_VLAN_CTAG_RX))
		features &= ~NETIF_F_HW_VLAN_CTAG_TX;

	return features;
}