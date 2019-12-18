#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iavf_adapter {TYPE_1__* vf_res; } ;
typedef  int netdev_features_t ;
struct TYPE_2__ {int vf_cap_flags; } ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int VIRTCHNL_VF_OFFLOAD_VLAN ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t iavf_fix_features(struct net_device *netdev,
					   netdev_features_t features)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);

	if (!(adapter->vf_res->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_VLAN))
		features &= ~(NETIF_F_HW_VLAN_CTAG_TX |
			      NETIF_F_HW_VLAN_CTAG_RX |
			      NETIF_F_HW_VLAN_CTAG_FILTER);

	return features;
}