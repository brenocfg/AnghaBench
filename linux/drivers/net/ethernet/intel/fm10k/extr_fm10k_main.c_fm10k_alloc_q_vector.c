#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct fm10k_ring {unsigned int queue_index; int /*<<< orphan*/  count; struct fm10k_q_vector* q_vector; int /*<<< orphan*/  l2_accel; int /*<<< orphan*/  netdev; int /*<<< orphan*/ * dev; } ;
struct TYPE_9__ {unsigned int count; int /*<<< orphan*/  itr_scale; int /*<<< orphan*/  itr; struct fm10k_ring* ring; } ;
struct TYPE_6__ {unsigned int count; int /*<<< orphan*/  itr_scale; int /*<<< orphan*/  itr; int /*<<< orphan*/  work_limit; struct fm10k_ring* ring; } ;
struct fm10k_q_vector {unsigned int v_idx; TYPE_4__ rx; TYPE_1__ tx; struct fm10k_ring* ring; struct fm10k_intfc* interface; int /*<<< orphan*/  napi; } ;
struct TYPE_7__ {int /*<<< orphan*/  itr_scale; } ;
struct TYPE_8__ {TYPE_2__ mac; } ;
struct fm10k_intfc {struct fm10k_ring** rx_ring; int /*<<< orphan*/  rx_ring_count; int /*<<< orphan*/  l2_accel; int /*<<< orphan*/  netdev; TYPE_5__* pdev; TYPE_3__ hw; int /*<<< orphan*/  rx_itr; struct fm10k_ring** tx_ring; int /*<<< orphan*/  tx_ring_count; int /*<<< orphan*/  tx_itr; struct fm10k_q_vector** q_vector; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FM10K_DEFAULT_TX_WORK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  fm10k_dbg_q_vector_init (struct fm10k_q_vector*) ; 
 int /*<<< orphan*/  fm10k_poll ; 
 struct fm10k_q_vector* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct fm10k_q_vector*,struct fm10k_ring*,int) ; 

__attribute__((used)) static int fm10k_alloc_q_vector(struct fm10k_intfc *interface,
				unsigned int v_count, unsigned int v_idx,
				unsigned int txr_count, unsigned int txr_idx,
				unsigned int rxr_count, unsigned int rxr_idx)
{
	struct fm10k_q_vector *q_vector;
	struct fm10k_ring *ring;
	int ring_count;

	ring_count = txr_count + rxr_count;

	/* allocate q_vector and rings */
	q_vector = kzalloc(struct_size(q_vector, ring, ring_count), GFP_KERNEL);
	if (!q_vector)
		return -ENOMEM;

	/* initialize NAPI */
	netif_napi_add(interface->netdev, &q_vector->napi,
		       fm10k_poll, NAPI_POLL_WEIGHT);

	/* tie q_vector and interface together */
	interface->q_vector[v_idx] = q_vector;
	q_vector->interface = interface;
	q_vector->v_idx = v_idx;

	/* initialize pointer to rings */
	ring = q_vector->ring;

	/* save Tx ring container info */
	q_vector->tx.ring = ring;
	q_vector->tx.work_limit = FM10K_DEFAULT_TX_WORK;
	q_vector->tx.itr = interface->tx_itr;
	q_vector->tx.itr_scale = interface->hw.mac.itr_scale;
	q_vector->tx.count = txr_count;

	while (txr_count) {
		/* assign generic ring traits */
		ring->dev = &interface->pdev->dev;
		ring->netdev = interface->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* apply Tx specific ring traits */
		ring->count = interface->tx_ring_count;
		ring->queue_index = txr_idx;

		/* assign ring to interface */
		interface->tx_ring[txr_idx] = ring;

		/* update count and index */
		txr_count--;
		txr_idx += v_count;

		/* push pointer to next ring */
		ring++;
	}

	/* save Rx ring container info */
	q_vector->rx.ring = ring;
	q_vector->rx.itr = interface->rx_itr;
	q_vector->rx.itr_scale = interface->hw.mac.itr_scale;
	q_vector->rx.count = rxr_count;

	while (rxr_count) {
		/* assign generic ring traits */
		ring->dev = &interface->pdev->dev;
		ring->netdev = interface->netdev;
		rcu_assign_pointer(ring->l2_accel, interface->l2_accel);

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* apply Rx specific ring traits */
		ring->count = interface->rx_ring_count;
		ring->queue_index = rxr_idx;

		/* assign ring to interface */
		interface->rx_ring[rxr_idx] = ring;

		/* update count and index */
		rxr_count--;
		rxr_idx += v_count;

		/* push pointer to next ring */
		ring++;
	}

	fm10k_dbg_q_vector_init(q_vector);

	return 0;
}