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
struct ibmvnic_adapter {int /*<<< orphan*/  resetting; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_rx_pools (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  clean_tx_pools (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  ibmvnic_disable_irqs (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  ibmvnic_napi_disable (struct ibmvnic_adapter*) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvnic_cleanup(struct net_device *netdev)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);

	/* ensure that transmissions are stopped if called by do_reset */
	if (test_bit(0, &adapter->resetting))
		netif_tx_disable(netdev);
	else
		netif_tx_stop_all_queues(netdev);

	ibmvnic_napi_disable(adapter);
	ibmvnic_disable_irqs(adapter);

	clean_rx_pools(adapter);
	clean_tx_pools(adapter);
}