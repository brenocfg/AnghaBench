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
struct TYPE_2__ {scalar_t__ rx_queues; scalar_t__ tx_queues; } ;
struct ibmvnic_adapter {scalar_t__ req_rx_queues; scalar_t__ req_tx_queues; TYPE_1__ desired; } ;
struct ethtool_channels {scalar_t__ rx_count; scalar_t__ tx_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int wait_for_reset (struct ibmvnic_adapter*) ; 

__attribute__((used)) static int ibmvnic_set_channels(struct net_device *netdev,
				struct ethtool_channels *channels)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);
	int ret;

	ret = 0;
	adapter->desired.rx_queues = channels->rx_count;
	adapter->desired.tx_queues = channels->tx_count;

	ret = wait_for_reset(adapter);

	if (!ret &&
	    (adapter->req_rx_queues != channels->rx_count ||
	     adapter->req_tx_queues != channels->tx_count))
		netdev_info(netdev,
			    "Could not match full channels request. Requested: RX %d, TX %d; Allowed: RX %llu, TX %llu\n",
			    channels->rx_count, channels->tx_count,
			    adapter->req_rx_queues, adapter->req_tx_queues);
	return ret;

}