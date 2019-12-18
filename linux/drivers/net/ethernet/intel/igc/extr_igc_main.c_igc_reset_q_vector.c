#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ring; } ;
struct TYPE_7__ {TYPE_4__* ring; } ;
struct igc_q_vector {int /*<<< orphan*/  napi; TYPE_2__ rx; TYPE_3__ tx; } ;
struct igc_adapter {int /*<<< orphan*/ ** rx_ring; int /*<<< orphan*/ ** tx_ring; struct igc_q_vector** q_vector; } ;
struct TYPE_8__ {size_t queue_index; } ;
struct TYPE_5__ {size_t queue_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igc_reset_q_vector(struct igc_adapter *adapter, int v_idx)
{
	struct igc_q_vector *q_vector = adapter->q_vector[v_idx];

	/* if we're coming from igc_set_interrupt_capability, the vectors are
	 * not yet allocated
	 */
	if (!q_vector)
		return;

	if (q_vector->tx.ring)
		adapter->tx_ring[q_vector->tx.ring->queue_index] = NULL;

	if (q_vector->rx.ring)
		adapter->rx_ring[q_vector->rx.ring->queue_index] = NULL;

	netif_napi_del(&q_vector->napi);
}