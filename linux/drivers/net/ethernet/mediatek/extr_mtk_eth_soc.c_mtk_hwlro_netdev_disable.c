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
struct mtk_mac {int id; scalar_t__ hwlro_ip_cnt; scalar_t__* hwlro_ip; struct mtk_eth* hw; } ;
struct mtk_eth {int dummy; } ;

/* Variables and functions */
 int MTK_MAX_LRO_IP_CNT ; 
 int /*<<< orphan*/  mtk_hwlro_inval_ipaddr (struct mtk_eth*,int) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mtk_hwlro_netdev_disable(struct net_device *dev)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;
	int i, hwlro_idx;

	for (i = 0; i < MTK_MAX_LRO_IP_CNT; i++) {
		mac->hwlro_ip[i] = 0;
		hwlro_idx = (mac->id * MTK_MAX_LRO_IP_CNT) + i;

		mtk_hwlro_inval_ipaddr(eth, hwlro_idx);
	}

	mac->hwlro_ip_cnt = 0;
}