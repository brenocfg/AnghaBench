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
struct i40e_vsi {int num_queue_pairs; int num_q_vectors; scalar_t__ base_vector; struct i40e_q_vector** q_vectors; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ring; scalar_t__ count; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ring; scalar_t__ count; } ;
struct i40e_q_vector {int num_ringpairs; TYPE_2__ tx; TYPE_1__ rx; scalar_t__ v_idx; scalar_t__ reg_idx; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  i40e_map_vector_to_qp (struct i40e_vsi*,int,int) ; 

__attribute__((used)) static void i40e_vsi_map_rings_to_vectors(struct i40e_vsi *vsi)
{
	int qp_remaining = vsi->num_queue_pairs;
	int q_vectors = vsi->num_q_vectors;
	int num_ringpairs;
	int v_start = 0;
	int qp_idx = 0;

	/* If we don't have enough vectors for a 1-to-1 mapping, we'll have to
	 * group them so there are multiple queues per vector.
	 * It is also important to go through all the vectors available to be
	 * sure that if we don't use all the vectors, that the remaining vectors
	 * are cleared. This is especially important when decreasing the
	 * number of queues in use.
	 */
	for (; v_start < q_vectors; v_start++) {
		struct i40e_q_vector *q_vector = vsi->q_vectors[v_start];

		num_ringpairs = DIV_ROUND_UP(qp_remaining, q_vectors - v_start);

		q_vector->num_ringpairs = num_ringpairs;
		q_vector->reg_idx = q_vector->v_idx + vsi->base_vector - 1;

		q_vector->rx.count = 0;
		q_vector->tx.count = 0;
		q_vector->rx.ring = NULL;
		q_vector->tx.ring = NULL;

		while (num_ringpairs--) {
			i40e_map_vector_to_qp(vsi, v_start, qp_idx);
			qp_idx++;
			qp_remaining--;
		}
	}
}