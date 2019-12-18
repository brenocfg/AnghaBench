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
struct net_device {int mtu; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_ALL_TSO ; 
 int NETIF_F_CSUM_MASK ; 

__attribute__((used)) static netdev_features_t
jme_fix_features(struct net_device *netdev, netdev_features_t features)
{
	if (netdev->mtu > 1900)
		features &= ~(NETIF_F_ALL_TSO | NETIF_F_CSUM_MASK);
	return features;
}