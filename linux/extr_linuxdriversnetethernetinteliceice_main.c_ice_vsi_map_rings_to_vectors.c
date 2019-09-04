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
struct ice_vsi {int num_q_vectors; int num_txq; int num_rxq; struct ice_ring** rx_rings; struct ice_ring** tx_rings; struct ice_q_vector** q_vectors; } ;
struct ice_ring {struct ice_ring* next; struct ice_q_vector* q_vector; } ;
struct TYPE_4__ {struct ice_ring* ring; } ;
struct TYPE_3__ {struct ice_ring* ring; } ;
struct ice_q_vector {int num_ring_tx; int num_ring_rx; TYPE_2__ rx; TYPE_1__ tx; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static void ice_vsi_map_rings_to_vectors(struct ice_vsi *vsi)
{
	int q_vectors = vsi->num_q_vectors;
	int tx_rings_rem, rx_rings_rem;
	int v_id;

	/* initially assigning remaining rings count to VSIs num queue value */
	tx_rings_rem = vsi->num_txq;
	rx_rings_rem = vsi->num_rxq;

	for (v_id = 0; v_id < q_vectors; v_id++) {
		struct ice_q_vector *q_vector = vsi->q_vectors[v_id];
		int tx_rings_per_v, rx_rings_per_v, q_id, q_base;

		/* Tx rings mapping to vector */
		tx_rings_per_v = DIV_ROUND_UP(tx_rings_rem, q_vectors - v_id);
		q_vector->num_ring_tx = tx_rings_per_v;
		q_vector->tx.ring = NULL;
		q_base = vsi->num_txq - tx_rings_rem;

		for (q_id = q_base; q_id < (q_base + tx_rings_per_v); q_id++) {
			struct ice_ring *tx_ring = vsi->tx_rings[q_id];

			tx_ring->q_vector = q_vector;
			tx_ring->next = q_vector->tx.ring;
			q_vector->tx.ring = tx_ring;
		}
		tx_rings_rem -= tx_rings_per_v;

		/* Rx rings mapping to vector */
		rx_rings_per_v = DIV_ROUND_UP(rx_rings_rem, q_vectors - v_id);
		q_vector->num_ring_rx = rx_rings_per_v;
		q_vector->rx.ring = NULL;
		q_base = vsi->num_rxq - rx_rings_rem;

		for (q_id = q_base; q_id < (q_base + rx_rings_per_v); q_id++) {
			struct ice_ring *rx_ring = vsi->rx_rings[q_id];

			rx_ring->q_vector = q_vector;
			rx_ring->next = q_vector->rx.ring;
			q_vector->rx.ring = rx_ring;
		}
		rx_rings_rem -= rx_rings_per_v;
	}
}