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
struct mtk_mac {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_LRO ; 
 int mtk_hwlro_get_ip_cnt (struct mtk_mac*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t mtk_fix_features(struct net_device *dev,
					  netdev_features_t features)
{
	if (!(features & NETIF_F_LRO)) {
		struct mtk_mac *mac = netdev_priv(dev);
		int ip_cnt = mtk_hwlro_get_ip_cnt(mac);

		if (ip_cnt) {
			netdev_info(dev, "RX flow is programmed, LRO should keep on\n");

			features |= NETIF_F_LRO;
		}
	}

	return features;
}