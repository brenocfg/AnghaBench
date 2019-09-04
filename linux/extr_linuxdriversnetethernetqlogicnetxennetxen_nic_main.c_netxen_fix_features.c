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
 int NETIF_F_LRO ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 

__attribute__((used)) static netdev_features_t netxen_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	if (!(features & NETIF_F_RXCSUM)) {
		netdev_info(dev, "disabling LRO as RXCSUM is off\n");

		features &= ~NETIF_F_LRO;
	}

	return features;
}