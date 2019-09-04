#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gfar_priv_rx_q {scalar_t__ next_to_clean; scalar_t__ next_to_use; int rx_ring_size; } ;

/* Variables and functions */

__attribute__((used)) static inline int gfar_rxbd_unused(struct gfar_priv_rx_q *rxq)
{
	if (rxq->next_to_clean > rxq->next_to_use)
		return rxq->next_to_clean - rxq->next_to_use - 1;

	return rxq->rx_ring_size + rxq->next_to_clean - rxq->next_to_use - 1;
}