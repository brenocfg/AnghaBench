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
struct net_device {scalar_t__ mtu; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  GMAC_OFFLOAD_FEATURES ; 
 scalar_t__ MTU_SIZE_BIT_MASK ; 
 scalar_t__ VLAN_HLEN ; 

__attribute__((used)) static netdev_features_t gmac_fix_features(struct net_device *netdev,
					   netdev_features_t features)
{
	if (netdev->mtu + ETH_HLEN + VLAN_HLEN > MTU_SIZE_BIT_MASK)
		features &= ~GMAC_OFFLOAD_FEATURES;

	return features;
}