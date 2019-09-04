#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct lan743x_adapter {TYPE_1__* rx; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_5__ {scalar_t__ frame_count; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ lan743x_csr_read (struct lan743x_adapter*,TYPE_1__) ; 
 TYPE_1__* lan743x_set0_hw_cnt_addr ; 
 TYPE_1__* lan743x_set2_hw_cnt_addr ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void lan743x_ethtool_get_ethtool_stats(struct net_device *netdev,
					      struct ethtool_stats *stats,
					      u64 *data)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);
	int data_index = 0;
	u32 buf;
	int i;

	for (i = 0; i < ARRAY_SIZE(lan743x_set0_hw_cnt_addr); i++) {
		buf = lan743x_csr_read(adapter, lan743x_set0_hw_cnt_addr[i]);
		data[data_index++] = (u64)buf;
	}
	for (i = 0; i < ARRAY_SIZE(adapter->rx); i++)
		data[data_index++] = (u64)(adapter->rx[i].frame_count);
	for (i = 0; i < ARRAY_SIZE(lan743x_set2_hw_cnt_addr); i++) {
		buf = lan743x_csr_read(adapter, lan743x_set2_hw_cnt_addr[i]);
		data[data_index++] = (u64)buf;
	}
}