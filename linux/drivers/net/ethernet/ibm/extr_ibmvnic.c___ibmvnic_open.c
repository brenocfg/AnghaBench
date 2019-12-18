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
struct ibmvnic_adapter {int state; int req_rx_queues; int req_tx_queues; int /*<<< orphan*/ * napi; TYPE_1__** tx_scrq; TYPE_1__** rx_scrq; } ;
typedef  enum vnic_state { ____Placeholder_vnic_state } vnic_state ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVNIC_LOGICAL_LNK_UP ; 
 int VNIC_CLOSED ; 
 int VNIC_OPEN ; 
 int VNIC_OPENING ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_scrq_irq (struct ibmvnic_adapter*,TYPE_1__*) ; 
 int /*<<< orphan*/  ibmvnic_napi_enable (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  release_resources (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  replenish_pools (struct ibmvnic_adapter*) ; 
 int set_link_state (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ibmvnic_open(struct net_device *netdev)
{
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);
	enum vnic_state prev_state = adapter->state;
	int i, rc;

	adapter->state = VNIC_OPENING;
	replenish_pools(adapter);
	ibmvnic_napi_enable(adapter);

	/* We're ready to receive frames, enable the sub-crq interrupts and
	 * set the logical link state to up
	 */
	for (i = 0; i < adapter->req_rx_queues; i++) {
		netdev_dbg(netdev, "Enabling rx_scrq[%d] irq\n", i);
		if (prev_state == VNIC_CLOSED)
			enable_irq(adapter->rx_scrq[i]->irq);
		enable_scrq_irq(adapter, adapter->rx_scrq[i]);
	}

	for (i = 0; i < adapter->req_tx_queues; i++) {
		netdev_dbg(netdev, "Enabling tx_scrq[%d] irq\n", i);
		if (prev_state == VNIC_CLOSED)
			enable_irq(adapter->tx_scrq[i]->irq);
		enable_scrq_irq(adapter, adapter->tx_scrq[i]);
	}

	rc = set_link_state(adapter, IBMVNIC_LOGICAL_LNK_UP);
	if (rc) {
		for (i = 0; i < adapter->req_rx_queues; i++)
			napi_disable(&adapter->napi[i]);
		release_resources(adapter);
		return rc;
	}

	netif_tx_start_all_queues(netdev);

	if (prev_state == VNIC_CLOSED) {
		for (i = 0; i < adapter->req_rx_queues; i++)
			napi_schedule(&adapter->napi[i]);
	}

	adapter->state = VNIC_OPEN;
	return rc;
}