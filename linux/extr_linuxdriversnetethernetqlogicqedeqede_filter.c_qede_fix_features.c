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
struct qede_dev {TYPE_1__* ndev; scalar_t__ xdp_prog; } ;
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int NETIF_F_GRO ; 
 int NETIF_F_GRO_HW ; 
 scalar_t__ PAGE_SIZE ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 

netdev_features_t qede_fix_features(struct net_device *dev,
				    netdev_features_t features)
{
	struct qede_dev *edev = netdev_priv(dev);

	if (edev->xdp_prog || edev->ndev->mtu > PAGE_SIZE ||
	    !(features & NETIF_F_GRO))
		features &= ~NETIF_F_GRO_HW;

	return features;
}