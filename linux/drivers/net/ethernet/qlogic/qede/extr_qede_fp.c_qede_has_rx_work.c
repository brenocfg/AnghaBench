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
typedef  scalar_t__ u16 ;
struct qede_rx_queue {int /*<<< orphan*/  rx_comp_ring; int /*<<< orphan*/ * hw_cons_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ qed_chain_get_cons_idx (int /*<<< orphan*/ *) ; 

bool qede_has_rx_work(struct qede_rx_queue *rxq)
{
	u16 hw_comp_cons, sw_comp_cons;

	/* Tell compiler that status block fields can change */
	barrier();

	hw_comp_cons = le16_to_cpu(*rxq->hw_cons_ptr);
	sw_comp_cons = qed_chain_get_cons_idx(&rxq->rx_comp_ring);

	return hw_comp_cons != sw_comp_cons;
}