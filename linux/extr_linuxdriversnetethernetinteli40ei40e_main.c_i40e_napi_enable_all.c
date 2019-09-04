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
struct i40e_vsi {int num_q_vectors; struct i40e_q_vector** q_vectors; int /*<<< orphan*/  netdev; } ;
struct TYPE_4__ {scalar_t__ ring; } ;
struct TYPE_3__ {scalar_t__ ring; } ;
struct i40e_q_vector {int /*<<< orphan*/  napi; TYPE_2__ tx; TYPE_1__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40e_napi_enable_all(struct i40e_vsi *vsi)
{
	int q_idx;

	if (!vsi->netdev)
		return;

	for (q_idx = 0; q_idx < vsi->num_q_vectors; q_idx++) {
		struct i40e_q_vector *q_vector = vsi->q_vectors[q_idx];

		if (q_vector->rx.ring || q_vector->tx.ring)
			napi_enable(&q_vector->napi);
	}
}