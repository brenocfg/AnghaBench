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
struct be_adapter {int num_rx_qs; int num_tx_qs; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ETHTOOL_RXSTATS_NUM ; 
 int ETHTOOL_STATS_NUM ; 
 int ETHTOOL_TESTS_NUM ; 
 int ETHTOOL_TXSTATS_NUM ; 
#define  ETH_SS_PRIV_FLAGS 130 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int /*<<< orphan*/  be_priv_flags ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_get_sset_count(struct net_device *netdev, int stringset)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	switch (stringset) {
	case ETH_SS_TEST:
		return ETHTOOL_TESTS_NUM;
	case ETH_SS_STATS:
		return ETHTOOL_STATS_NUM +
			adapter->num_rx_qs * ETHTOOL_RXSTATS_NUM +
			adapter->num_tx_qs * ETHTOOL_TXSTATS_NUM;
	case ETH_SS_PRIV_FLAGS:
		return ARRAY_SIZE(be_priv_flags);
	default:
		return -EINVAL;
	}
}