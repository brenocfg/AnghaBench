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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_mmc_stats ) (struct xlgmac_pdata*) ;} ;
struct xlgmac_pdata {TYPE_1__ hw_ops; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_4__ {int stat_offset; } ;

/* Variables and functions */
 int XLGMAC_STATS_COUNT ; 
 struct xlgmac_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct xlgmac_pdata*) ; 
 TYPE_2__* xlgmac_gstring_stats ; 

__attribute__((used)) static void xlgmac_ethtool_get_ethtool_stats(struct net_device *netdev,
					     struct ethtool_stats *stats,
					     u64 *data)
{
	struct xlgmac_pdata *pdata = netdev_priv(netdev);
	u8 *stat;
	int i;

	pdata->hw_ops.read_mmc_stats(pdata);
	for (i = 0; i < XLGMAC_STATS_COUNT; i++) {
		stat = (u8 *)pdata + xlgmac_gstring_stats[i].stat_offset;
		*data++ = *(u64 *)stat;
	}
}