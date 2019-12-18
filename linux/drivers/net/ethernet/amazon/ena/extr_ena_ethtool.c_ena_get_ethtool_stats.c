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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct ena_stats {scalar_t__ stat_offset; } ;
struct ena_adapter {int /*<<< orphan*/  syncp; int /*<<< orphan*/  dev_stats; } ;

/* Variables and functions */
 int ENA_STATS_ARRAY_GLOBAL ; 
 int /*<<< orphan*/  ena_dev_admin_queue_stats (struct ena_adapter*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ena_queue_stats (struct ena_adapter*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ena_safe_update_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ena_stats* ena_stats_global_strings ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ena_get_ethtool_stats(struct net_device *netdev,
				  struct ethtool_stats *stats,
				  u64 *data)
{
	struct ena_adapter *adapter = netdev_priv(netdev);
	const struct ena_stats *ena_stats;
	u64 *ptr;
	int i;

	for (i = 0; i < ENA_STATS_ARRAY_GLOBAL; i++) {
		ena_stats = &ena_stats_global_strings[i];

		ptr = (u64 *)((uintptr_t)&adapter->dev_stats +
			(uintptr_t)ena_stats->stat_offset);

		ena_safe_update_stat(ptr, data++, &adapter->syncp);
	}

	ena_queue_stats(adapter, &data);
	ena_dev_admin_queue_stats(adapter, &data);
}