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
struct sh_eth_private {TYPE_1__* cd; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;
struct TYPE_2__ {scalar_t__ rx_csum; } ;

/* Variables and functions */
 int NETIF_F_RXCSUM ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_set_rx_csum (struct net_device*,int) ; 

__attribute__((used)) static int sh_eth_set_features(struct net_device *ndev,
			       netdev_features_t features)
{
	netdev_features_t changed = ndev->features ^ features;
	struct sh_eth_private *mdp = netdev_priv(ndev);

	if (changed & NETIF_F_RXCSUM && mdp->cd->rx_csum)
		sh_eth_set_rx_csum(ndev, features & NETIF_F_RXCSUM);

	ndev->features = features;

	return 0;
}