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
struct i40e_vsi {struct i40e_ring** xdp_rings; struct i40e_ring** rx_rings; struct i40e_ring** tx_rings; struct i40e_q_vector** q_vectors; } ;
struct i40e_ring {struct i40e_ring* next; struct i40e_q_vector* q_vector; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; struct i40e_ring* ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; struct i40e_ring* ring; } ;
struct i40e_q_vector {TYPE_2__ rx; TYPE_1__ tx; } ;

/* Variables and functions */
 scalar_t__ i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 

__attribute__((used)) static void i40e_map_vector_to_qp(struct i40e_vsi *vsi, int v_idx, int qp_idx)
{
	struct i40e_q_vector *q_vector = vsi->q_vectors[v_idx];
	struct i40e_ring *tx_ring = vsi->tx_rings[qp_idx];
	struct i40e_ring *rx_ring = vsi->rx_rings[qp_idx];

	tx_ring->q_vector = q_vector;
	tx_ring->next = q_vector->tx.ring;
	q_vector->tx.ring = tx_ring;
	q_vector->tx.count++;

	/* Place XDP Tx ring in the same q_vector ring list as regular Tx */
	if (i40e_enabled_xdp_vsi(vsi)) {
		struct i40e_ring *xdp_ring = vsi->xdp_rings[qp_idx];

		xdp_ring->q_vector = q_vector;
		xdp_ring->next = q_vector->tx.ring;
		q_vector->tx.ring = xdp_ring;
		q_vector->tx.count++;
	}

	rx_ring->q_vector = q_vector;
	rx_ring->next = q_vector->rx.ring;
	q_vector->rx.ring = rx_ring;
	q_vector->rx.count++;
}