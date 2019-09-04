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
struct net_device {int hw_features; int vlan_features; int features; } ;

/* Variables and functions */
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_SG ; 

__attribute__((used)) static void netdev_features_init(struct net_device *netdev)
{
	netdev->hw_features = NETIF_F_SG | NETIF_F_HIGHDMA;

	netdev->vlan_features = netdev->hw_features;

	netdev->features = netdev->hw_features | NETIF_F_HW_VLAN_CTAG_FILTER;
}