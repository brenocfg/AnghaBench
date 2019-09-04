#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct i40evf_adapter {unsigned int num_active_queues; TYPE_4__* rx_rings; TYPE_2__* tx_rings; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_10__ {int stat_offset; } ;
struct TYPE_8__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct TYPE_9__ {TYPE_3__ stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct TYPE_7__ {TYPE_1__ stats; } ;

/* Variables and functions */
 unsigned int I40EVF_GLOBAL_STATS_LEN ; 
 TYPE_5__* i40evf_gstrings_stats ; 
 struct i40evf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void i40evf_get_ethtool_stats(struct net_device *netdev,
				     struct ethtool_stats *stats, u64 *data)
{
	struct i40evf_adapter *adapter = netdev_priv(netdev);
	unsigned int i, j;
	char *p;

	for (i = 0; i < I40EVF_GLOBAL_STATS_LEN; i++) {
		p = (char *)adapter + i40evf_gstrings_stats[i].stat_offset;
		data[i] =  *(u64 *)p;
	}
	for (j = 0; j < adapter->num_active_queues; j++) {
		data[i++] = adapter->tx_rings[j].stats.packets;
		data[i++] = adapter->tx_rings[j].stats.bytes;
	}
	for (j = 0; j < adapter->num_active_queues; j++) {
		data[i++] = adapter->rx_rings[j].stats.packets;
		data[i++] = adapter->rx_rings[j].stats.bytes;
	}
}