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
typedef  int /*<<< orphan*/  u32 ;
struct pch_gbe_stats {int offset; int size; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  stats; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int PCH_GBE_GLOBAL_STATS_LEN ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 struct pch_gbe_stats* pch_gbe_gstrings_stats ; 
 int /*<<< orphan*/  pch_gbe_update_stats (struct pch_gbe_adapter*) ; 

__attribute__((used)) static void pch_gbe_get_ethtool_stats(struct net_device *netdev,
				  struct ethtool_stats *stats, u64 *data)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	int i;
	const struct pch_gbe_stats *gstats = pch_gbe_gstrings_stats;
	char *hw_stats = (char *)&adapter->stats;

	pch_gbe_update_stats(adapter);
	for (i = 0; i < PCH_GBE_GLOBAL_STATS_LEN; i++) {
		char *p = hw_stats + gstats->offset;
		data[i] = gstats->size == sizeof(u64) ? *(u64 *)p:(*(u32 *)p);
		gstats++;
	}
}