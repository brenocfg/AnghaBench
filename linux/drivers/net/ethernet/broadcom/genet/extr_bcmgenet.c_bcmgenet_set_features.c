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
struct net_device {int features; int wanted_features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int bcmgenet_set_rx_csum (struct net_device*,int) ; 
 int bcmgenet_set_tx_csum (struct net_device*,int) ; 

__attribute__((used)) static int bcmgenet_set_features(struct net_device *dev,
				 netdev_features_t features)
{
	netdev_features_t changed = features ^ dev->features;
	netdev_features_t wanted = dev->wanted_features;
	int ret = 0;

	if (changed & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM))
		ret = bcmgenet_set_tx_csum(dev, wanted);
	if (changed & (NETIF_F_RXCSUM))
		ret = bcmgenet_set_rx_csum(dev, wanted);

	return ret;
}