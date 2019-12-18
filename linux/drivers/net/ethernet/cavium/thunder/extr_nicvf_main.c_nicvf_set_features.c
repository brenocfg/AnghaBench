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
struct nicvf {int dummy; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_LOOPBACK ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int nicvf_config_loopback (struct nicvf*,int) ; 
 int /*<<< orphan*/  nicvf_config_vlan_stripping (struct nicvf*,int) ; 

__attribute__((used)) static int nicvf_set_features(struct net_device *netdev,
			      netdev_features_t features)
{
	struct nicvf *nic = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	if (changed & NETIF_F_HW_VLAN_CTAG_RX)
		nicvf_config_vlan_stripping(nic, features);

	if ((changed & NETIF_F_LOOPBACK) && netif_running(netdev))
		return nicvf_config_loopback(nic, features);

	return 0;
}