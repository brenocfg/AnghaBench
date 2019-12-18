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
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  ravb_set_rx_csum (struct net_device*,int) ; 

__attribute__((used)) static int ravb_set_features(struct net_device *ndev,
			     netdev_features_t features)
{
	netdev_features_t changed = ndev->features ^ features;

	if (changed & NETIF_F_RXCSUM)
		ravb_set_rx_csum(ndev, features & NETIF_F_RXCSUM);

	ndev->features = features;

	return 0;
}