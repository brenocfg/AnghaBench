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
struct i40e_vsi {int /*<<< orphan*/  netdev; struct i40e_ring** rx_rings; } ;
struct i40e_ring {struct i40e_q_vector* q_vector; } ;
struct TYPE_4__ {scalar_t__ ring; } ;
struct TYPE_3__ {scalar_t__ ring; } ;
struct i40e_q_vector {int /*<<< orphan*/  napi; TYPE_2__ tx; TYPE_1__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40e_queue_pair_toggle_napi(struct i40e_vsi *vsi, int queue_pair,
					bool enable)
{
	struct i40e_ring *rxr = vsi->rx_rings[queue_pair];
	struct i40e_q_vector *q_vector = rxr->q_vector;

	if (!vsi->netdev)
		return;

	/* All rings in a qp belong to the same qvector. */
	if (q_vector->rx.ring || q_vector->tx.ring) {
		if (enable)
			napi_enable(&q_vector->napi);
		else
			napi_disable(&q_vector->napi);
	}
}