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
struct ethtool_coalesce {int rx_coalesce_usecs; } ;
struct e1000_adapter {int itr_setting; } ;

/* Variables and functions */
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int e1000_get_coalesce(struct net_device *netdev,
			      struct ethtool_coalesce *ec)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);

	if (adapter->itr_setting <= 4)
		ec->rx_coalesce_usecs = adapter->itr_setting;
	else
		ec->rx_coalesce_usecs = 1000000 / adapter->itr_setting;

	return 0;
}