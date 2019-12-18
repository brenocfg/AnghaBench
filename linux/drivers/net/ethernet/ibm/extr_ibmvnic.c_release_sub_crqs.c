#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ibmvnic_adapter {int num_active_tx_scrqs; int num_active_rx_scrqs; TYPE_1__** rx_scrq; int /*<<< orphan*/  netdev; TYPE_1__** tx_scrq; } ;
struct TYPE_4__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_1__**) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  release_sub_crq_queue (struct ibmvnic_adapter*,TYPE_1__*,int) ; 

__attribute__((used)) static void release_sub_crqs(struct ibmvnic_adapter *adapter, bool do_h_free)
{
	int i;

	if (adapter->tx_scrq) {
		for (i = 0; i < adapter->num_active_tx_scrqs; i++) {
			if (!adapter->tx_scrq[i])
				continue;

			netdev_dbg(adapter->netdev, "Releasing tx_scrq[%d]\n",
				   i);
			if (adapter->tx_scrq[i]->irq) {
				free_irq(adapter->tx_scrq[i]->irq,
					 adapter->tx_scrq[i]);
				irq_dispose_mapping(adapter->tx_scrq[i]->irq);
				adapter->tx_scrq[i]->irq = 0;
			}

			release_sub_crq_queue(adapter, adapter->tx_scrq[i],
					      do_h_free);
		}

		kfree(adapter->tx_scrq);
		adapter->tx_scrq = NULL;
		adapter->num_active_tx_scrqs = 0;
	}

	if (adapter->rx_scrq) {
		for (i = 0; i < adapter->num_active_rx_scrqs; i++) {
			if (!adapter->rx_scrq[i])
				continue;

			netdev_dbg(adapter->netdev, "Releasing rx_scrq[%d]\n",
				   i);
			if (adapter->rx_scrq[i]->irq) {
				free_irq(adapter->rx_scrq[i]->irq,
					 adapter->rx_scrq[i]);
				irq_dispose_mapping(adapter->rx_scrq[i]->irq);
				adapter->rx_scrq[i]->irq = 0;
			}

			release_sub_crq_queue(adapter, adapter->rx_scrq[i],
					      do_h_free);
		}

		kfree(adapter->rx_scrq);
		adapter->rx_scrq = NULL;
		adapter->num_active_rx_scrqs = 0;
	}
}