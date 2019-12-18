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
 int qlge_update_hw_vlan_features (struct net_device*,int) ; 
 int /*<<< orphan*/  qlge_vlan_mode (struct net_device*,int) ; 

__attribute__((used)) static int qlge_set_features(struct net_device *ndev,
	netdev_features_t features)
{
	netdev_features_t changed = ndev->features ^ features;
	int err;

	if (changed & NETIF_F_HW_VLAN_CTAG_RX) {
		/* Update the behavior of vlan accel in the adapter */
		err = qlge_update_hw_vlan_features(ndev, features);
		if (err)
			return err;

		qlge_vlan_mode(ndev, features);
	}

	return 0;
}