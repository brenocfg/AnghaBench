#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ena_adapter {int requested_tx_ring_size; int requested_rx_ring_size; int /*<<< orphan*/  netdev; TYPE_2__* rx_ring; TYPE_1__* tx_ring; } ;
struct TYPE_4__ {int ring_size; } ;
struct TYPE_3__ {int ring_size; } ;

/* Variables and functions */
 int ENA_MIN_RING_SIZE ; 
 int ENOMEM ; 
 int ena_create_all_io_rx_queues (struct ena_adapter*) ; 
 int ena_create_all_io_tx_queues (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_destroy_all_tx_queues (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_all_io_rx_resources (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_free_all_io_tx_resources (struct ena_adapter*) ; 
 int ena_setup_all_rx_resources (struct ena_adapter*) ; 
 int ena_setup_all_tx_resources (struct ena_adapter*) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  set_io_rings_size (struct ena_adapter*,int,int) ; 

__attribute__((used)) static int create_queues_with_size_backoff(struct ena_adapter *adapter)
{
	int rc, cur_rx_ring_size, cur_tx_ring_size;
	int new_rx_ring_size, new_tx_ring_size;

	/* current queue sizes might be set to smaller than the requested
	 * ones due to past queue allocation failures.
	 */
	set_io_rings_size(adapter, adapter->requested_tx_ring_size,
			  adapter->requested_rx_ring_size);

	while (1) {
		rc = ena_setup_all_tx_resources(adapter);
		if (rc)
			goto err_setup_tx;

		rc = ena_create_all_io_tx_queues(adapter);
		if (rc)
			goto err_create_tx_queues;

		rc = ena_setup_all_rx_resources(adapter);
		if (rc)
			goto err_setup_rx;

		rc = ena_create_all_io_rx_queues(adapter);
		if (rc)
			goto err_create_rx_queues;

		return 0;

err_create_rx_queues:
		ena_free_all_io_rx_resources(adapter);
err_setup_rx:
		ena_destroy_all_tx_queues(adapter);
err_create_tx_queues:
		ena_free_all_io_tx_resources(adapter);
err_setup_tx:
		if (rc != -ENOMEM) {
			netif_err(adapter, ifup, adapter->netdev,
				  "Queue creation failed with error code %d\n",
				  rc);
			return rc;
		}

		cur_tx_ring_size = adapter->tx_ring[0].ring_size;
		cur_rx_ring_size = adapter->rx_ring[0].ring_size;

		netif_err(adapter, ifup, adapter->netdev,
			  "Not enough memory to create queues with sizes TX=%d, RX=%d\n",
			  cur_tx_ring_size, cur_rx_ring_size);

		new_tx_ring_size = cur_tx_ring_size;
		new_rx_ring_size = cur_rx_ring_size;

		/* Decrease the size of the larger queue, or
		 * decrease both if they are the same size.
		 */
		if (cur_rx_ring_size <= cur_tx_ring_size)
			new_tx_ring_size = cur_tx_ring_size / 2;
		if (cur_rx_ring_size >= cur_tx_ring_size)
			new_rx_ring_size = cur_rx_ring_size / 2;

		if (new_tx_ring_size < ENA_MIN_RING_SIZE ||
		    new_rx_ring_size < ENA_MIN_RING_SIZE) {
			netif_err(adapter, ifup, adapter->netdev,
				  "Queue creation failed with the smallest possible queue size of %d for both queues. Not retrying with smaller queues\n",
				  ENA_MIN_RING_SIZE);
			return rc;
		}

		netif_err(adapter, ifup, adapter->netdev,
			  "Retrying queue creation with sizes TX=%d, RX=%d\n",
			  new_tx_ring_size,
			  new_rx_ring_size);

		set_io_rings_size(adapter, new_tx_ring_size,
				  new_rx_ring_size);
	}
}