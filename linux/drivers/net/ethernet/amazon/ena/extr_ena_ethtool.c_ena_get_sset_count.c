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
struct ena_adapter {int num_queues; } ;

/* Variables and functions */
 int ENA_STATS_ARRAY_ENA_COM ; 
 int ENA_STATS_ARRAY_GLOBAL ; 
 int ENA_STATS_ARRAY_RX ; 
 int ENA_STATS_ARRAY_TX ; 
 int EOPNOTSUPP ; 
 int ETH_SS_STATS ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 

int ena_get_sset_count(struct net_device *netdev, int sset)
{
	struct ena_adapter *adapter = netdev_priv(netdev);

	if (sset != ETH_SS_STATS)
		return -EOPNOTSUPP;

	return  adapter->num_queues * (ENA_STATS_ARRAY_TX + ENA_STATS_ARRAY_RX)
		+ ENA_STATS_ARRAY_GLOBAL + ENA_STATS_ARRAY_ENA_COM;
}