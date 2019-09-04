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
 int NETIF_F_RXHASH ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static netdev_features_t vxge_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	netdev_features_t changed = dev->features ^ features;

	/* Enabling RTH requires some of the logic in vxge_device_register and a
	 * vpath reset.  Due to these restrictions, only allow modification
	 * while the interface is down.
	 */
	if ((changed & NETIF_F_RXHASH) && netif_running(dev))
		features ^= NETIF_F_RXHASH;

	return features;
}