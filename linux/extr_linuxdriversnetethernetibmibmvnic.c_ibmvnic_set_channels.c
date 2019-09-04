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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_queues; int /*<<< orphan*/  rx_queues; } ;
struct ibmvnic_adapter {TYPE_1__ desired; } ;
struct ethtool_channels {int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; } ;

/* Variables and functions */
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int wait_for_reset (struct ibmvnic_adapter*) ; 

__attribute__((used)) static int ibmvnic_set_channels(struct net_device *netdev,
				struct ethtool_channels *channels)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);

	adapter->desired.rx_queues = channels->rx_count;
	adapter->desired.tx_queues = channels->tx_count;

	return wait_for_reset(adapter);
}