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
struct xgbe_prv_data {int tx_ring_count; int rx_ring_count; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int /*<<< orphan*/  XGBE_STATS_COUNT ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int xgbe_get_sset_count(struct net_device *netdev, int stringset)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	int ret;

	switch (stringset) {
	case ETH_SS_STATS:
		ret = XGBE_STATS_COUNT +
		      (pdata->tx_ring_count * 2) +
		      (pdata->rx_ring_count * 2);
		break;

	default:
		ret = -EOPNOTSUPP;
	}

	return ret;
}