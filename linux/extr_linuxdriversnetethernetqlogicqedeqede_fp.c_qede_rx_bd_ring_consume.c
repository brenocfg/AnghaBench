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
struct qede_rx_queue {int /*<<< orphan*/  sw_rx_cons; int /*<<< orphan*/  rx_bd_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_chain_consume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void qede_rx_bd_ring_consume(struct qede_rx_queue *rxq)
{
	qed_chain_consume(&rxq->rx_bd_ring);
	rxq->sw_rx_cons++;
}