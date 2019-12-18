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
struct igb_adapter {int rx_itr_setting; int flags; int tx_itr_setting; } ;
struct ethtool_coalesce {int rx_coalesce_usecs; int tx_coalesce_usecs; } ;

/* Variables and functions */
 int IGB_FLAG_QUEUE_PAIRS ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_get_coalesce(struct net_device *netdev,
			    struct ethtool_coalesce *ec)
{
	struct igb_adapter *adapter = netdev_priv(netdev);

	if (adapter->rx_itr_setting <= 3)
		ec->rx_coalesce_usecs = adapter->rx_itr_setting;
	else
		ec->rx_coalesce_usecs = adapter->rx_itr_setting >> 2;

	if (!(adapter->flags & IGB_FLAG_QUEUE_PAIRS)) {
		if (adapter->tx_itr_setting <= 3)
			ec->tx_coalesce_usecs = adapter->tx_itr_setting;
		else
			ec->tx_coalesce_usecs = adapter->tx_itr_setting >> 2;
	}

	return 0;
}