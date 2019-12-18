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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct netxen_adapter {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_2__ {int stat_offset; int sizeof_stat; } ;

/* Variables and functions */
 int NETXEN_NIC_STATS_LEN ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 TYPE_1__* netxen_nic_gstrings_stats ; 

__attribute__((used)) static void
netxen_nic_get_ethtool_stats(struct net_device *dev,
			     struct ethtool_stats *stats, u64 *data)
{
	struct netxen_adapter *adapter = netdev_priv(dev);
	int index;

	for (index = 0; index < NETXEN_NIC_STATS_LEN; index++) {
		char *p =
		    (char *)adapter +
		    netxen_nic_gstrings_stats[index].stat_offset;
		data[index] =
		    (netxen_nic_gstrings_stats[index].sizeof_stat ==
		     sizeof(u64)) ? *(u64 *) p : *(u32 *) p;
	}
}