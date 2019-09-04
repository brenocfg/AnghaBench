#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vstats ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct opa_vnic_stats {int /*<<< orphan*/  netstats; } ;
struct opa_vnic_adapter {int /*<<< orphan*/  stats_lock; TYPE_1__* rn_ops; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_4__ {int stat_offset; int sizeof_stat; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ndo_get_stats64 ) (struct net_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int VNIC_STATS_LEN ; 
 int /*<<< orphan*/  memset (struct opa_vnic_stats*,int /*<<< orphan*/ ,int) ; 
 struct opa_vnic_adapter* opa_vnic_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ *) ; 
 TYPE_2__* vnic_gstrings_stats ; 

__attribute__((used)) static void vnic_get_ethtool_stats(struct net_device *netdev,
				   struct ethtool_stats *stats, u64 *data)
{
	struct opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	struct opa_vnic_stats vstats;
	int i;

	memset(&vstats, 0, sizeof(vstats));
	spin_lock(&adapter->stats_lock);
	adapter->rn_ops->ndo_get_stats64(netdev, &vstats.netstats);
	spin_unlock(&adapter->stats_lock);
	for (i = 0; i < VNIC_STATS_LEN; i++) {
		char *p = (char *)&vstats + vnic_gstrings_stats[i].stat_offset;

		data[i] = (vnic_gstrings_stats[i].sizeof_stat ==
			   sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}
}