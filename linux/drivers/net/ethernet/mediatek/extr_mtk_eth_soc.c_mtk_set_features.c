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
 int NETIF_F_LRO ; 
 int /*<<< orphan*/  mtk_hwlro_netdev_disable (struct net_device*) ; 

__attribute__((used)) static int mtk_set_features(struct net_device *dev, netdev_features_t features)
{
	int err = 0;

	if (!((dev->features ^ features) & NETIF_F_LRO))
		return 0;

	if (!(features & NETIF_F_LRO))
		mtk_hwlro_netdev_disable(dev);

	return err;
}