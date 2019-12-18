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
struct igc_ring {unsigned int queue_index; int /*<<< orphan*/  count; struct igc_q_vector* q_vector; int /*<<< orphan*/  netdev; int /*<<< orphan*/ * dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  work_limit; } ;
struct igc_q_vector {int itr_val; TYPE_2__ rx; TYPE_2__ tx; struct igc_ring* ring; scalar_t__ itr_register; struct igc_adapter* adapter; int /*<<< orphan*/  napi; } ;
struct igc_adapter {int rx_itr_setting; int tx_itr_setting; struct igc_ring** rx_ring; int /*<<< orphan*/  rx_ring_count; int /*<<< orphan*/  netdev; TYPE_1__* pdev; struct igc_ring** tx_ring; int /*<<< orphan*/  tx_ring_count; scalar_t__ io_addr; int /*<<< orphan*/  tx_work_limit; struct igc_q_vector** q_vector; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IGC_EITR (int /*<<< orphan*/ ) ; 
 int IGC_START_ITR ; 
 int /*<<< orphan*/  igc_add_ring (struct igc_ring*,TYPE_2__*) ; 
 int /*<<< orphan*/  igc_poll ; 
 struct igc_q_vector* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct igc_q_vector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  struct_size (struct igc_q_vector*,struct igc_ring*,int) ; 

__attribute__((used)) static int igc_alloc_q_vector(struct igc_adapter *adapter,
			      unsigned int v_count, unsigned int v_idx,
			      unsigned int txr_count, unsigned int txr_idx,
			      unsigned int rxr_count, unsigned int rxr_idx)
{
	struct igc_q_vector *q_vector;
	struct igc_ring *ring;
	int ring_count;

	/* igc only supports 1 Tx and/or 1 Rx queue per vector */
	if (txr_count > 1 || rxr_count > 1)
		return -ENOMEM;

	ring_count = txr_count + rxr_count;

	/* allocate q_vector and rings */
	q_vector = adapter->q_vector[v_idx];
	if (!q_vector)
		q_vector = kzalloc(struct_size(q_vector, ring, ring_count),
				   GFP_KERNEL);
	else
		memset(q_vector, 0, struct_size(q_vector, ring, ring_count));
	if (!q_vector)
		return -ENOMEM;

	/* initialize NAPI */
	netif_napi_add(adapter->netdev, &q_vector->napi,
		       igc_poll, 64);

	/* tie q_vector and adapter together */
	adapter->q_vector[v_idx] = q_vector;
	q_vector->adapter = adapter;

	/* initialize work limits */
	q_vector->tx.work_limit = adapter->tx_work_limit;

	/* initialize ITR configuration */
	q_vector->itr_register = adapter->io_addr + IGC_EITR(0);
	q_vector->itr_val = IGC_START_ITR;

	/* initialize pointer to rings */
	ring = q_vector->ring;

	/* initialize ITR */
	if (rxr_count) {
		/* rx or rx/tx vector */
		if (!adapter->rx_itr_setting || adapter->rx_itr_setting > 3)
			q_vector->itr_val = adapter->rx_itr_setting;
	} else {
		/* tx only vector */
		if (!adapter->tx_itr_setting || adapter->tx_itr_setting > 3)
			q_vector->itr_val = adapter->tx_itr_setting;
	}

	if (txr_count) {
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Tx values */
		igc_add_ring(ring, &q_vector->tx);

		/* apply Tx specific ring traits */
		ring->count = adapter->tx_ring_count;
		ring->queue_index = txr_idx;

		/* assign ring to adapter */
		adapter->tx_ring[txr_idx] = ring;

		/* push pointer to next ring */
		ring++;
	}

	if (rxr_count) {
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Rx values */
		igc_add_ring(ring, &q_vector->rx);

		/* apply Rx specific ring traits */
		ring->count = adapter->rx_ring_count;
		ring->queue_index = rxr_idx;

		/* assign ring to adapter */
		adapter->rx_ring[rxr_idx] = ring;
	}

	return 0;
}