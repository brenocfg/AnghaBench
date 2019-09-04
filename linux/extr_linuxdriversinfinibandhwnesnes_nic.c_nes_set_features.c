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
typedef  int u32 ;
struct net_device {int features; } ;
struct nes_vnic {struct nes_device* nesdev; } ;
struct nes_device {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  nes_vlan_mode (struct net_device*,struct nes_device*,int) ; 
 struct nes_vnic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nes_set_features(struct net_device *netdev, netdev_features_t features)
{
	struct nes_vnic *nesvnic = netdev_priv(netdev);
	struct nes_device *nesdev = nesvnic->nesdev;
	u32 changed = netdev->features ^ features;

	if (changed & NETIF_F_HW_VLAN_CTAG_RX)
		nes_vlan_mode(netdev, nesdev, features);

	return 0;
}