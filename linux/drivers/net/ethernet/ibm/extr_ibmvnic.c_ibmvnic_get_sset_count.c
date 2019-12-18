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
struct ibmvnic_adapter {int req_tx_queues; int req_rx_queues; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_PRIV_FLAGS 129 
#define  ETH_SS_STATS 128 
 int NUM_RX_STATS ; 
 int NUM_TX_STATS ; 
 int /*<<< orphan*/  ibmvnic_priv_flags ; 
 int /*<<< orphan*/  ibmvnic_stats ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ibmvnic_get_sset_count(struct net_device *dev, int sset)
{
	struct ibmvnic_adapter *adapter = netdev_priv(dev);

	switch (sset) {
	case ETH_SS_STATS:
		return ARRAY_SIZE(ibmvnic_stats) +
		       adapter->req_tx_queues * NUM_TX_STATS +
		       adapter->req_rx_queues * NUM_RX_STATS;
	case ETH_SS_PRIV_FLAGS:
		return ARRAY_SIZE(ibmvnic_priv_flags);
	default:
		return -EOPNOTSUPP;
	}
}