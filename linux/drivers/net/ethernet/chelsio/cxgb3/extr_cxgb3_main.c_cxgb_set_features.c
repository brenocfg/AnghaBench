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
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  cxgb_vlan_mode (struct net_device*,int) ; 

__attribute__((used)) static int cxgb_set_features(struct net_device *dev, netdev_features_t features)
{
	netdev_features_t changed = dev->features ^ features;

	if (changed & NETIF_F_HW_VLAN_CTAG_RX)
		cxgb_vlan_mode(dev, features);

	return 0;
}