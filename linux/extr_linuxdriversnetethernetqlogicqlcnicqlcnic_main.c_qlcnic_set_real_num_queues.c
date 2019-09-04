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
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_adapter {struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_set_real_num_queues(struct qlcnic_adapter *adapter,
				      u8 tx_queues, u8 rx_queues)
{
	struct net_device *netdev = adapter->netdev;
	int err = 0;

	if (tx_queues) {
		err = netif_set_real_num_tx_queues(netdev, tx_queues);
		if (err) {
			netdev_err(netdev, "failed to set %d Tx queues\n",
				   tx_queues);
			return err;
		}
	}

	if (rx_queues) {
		err = netif_set_real_num_rx_queues(netdev, rx_queues);
		if (err)
			netdev_err(netdev, "failed to set %d Rx queues\n",
				   rx_queues);
	}

	return err;
}