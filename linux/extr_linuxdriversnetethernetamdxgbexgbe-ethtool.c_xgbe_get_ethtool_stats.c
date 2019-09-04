#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int /*<<< orphan*/ * rxq_bytes; int /*<<< orphan*/ * rxq_packets; int /*<<< orphan*/ * txq_bytes; int /*<<< orphan*/ * txq_packets; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* read_mmc_stats ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int tx_ring_count; int rx_ring_count; TYPE_2__ ext_stats; TYPE_1__ hw_if; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_6__ {int stat_offset; } ;

/* Variables and functions */
 int XGBE_STATS_COUNT ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 TYPE_3__* xgbe_gstring_stats ; 

__attribute__((used)) static void xgbe_get_ethtool_stats(struct net_device *netdev,
				   struct ethtool_stats *stats, u64 *data)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	u8 *stat;
	int i;

	pdata->hw_if.read_mmc_stats(pdata);
	for (i = 0; i < XGBE_STATS_COUNT; i++) {
		stat = (u8 *)pdata + xgbe_gstring_stats[i].stat_offset;
		*data++ = *(u64 *)stat;
	}
	for (i = 0; i < pdata->tx_ring_count; i++) {
		*data++ = pdata->ext_stats.txq_packets[i];
		*data++ = pdata->ext_stats.txq_bytes[i];
	}
	for (i = 0; i < pdata->rx_ring_count; i++) {
		*data++ = pdata->ext_stats.rxq_packets[i];
		*data++ = pdata->ext_stats.rxq_bytes[i];
	}
}