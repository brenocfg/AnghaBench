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

/* Variables and functions */
 int DPAA2_ETH_NUM_EXTRA_STATS ; 
 int DPAA2_ETH_NUM_STATS ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 

__attribute__((used)) static int dpaa2_eth_get_sset_count(struct net_device *net_dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS: /* ethtool_get_stats(), ethtool_get_drvinfo() */
		return DPAA2_ETH_NUM_STATS + DPAA2_ETH_NUM_EXTRA_STATS;
	default:
		return -EOPNOTSUPP;
	}
}