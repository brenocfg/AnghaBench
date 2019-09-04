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
struct qede_tx_queue {int /*<<< orphan*/  tx_pbl; int /*<<< orphan*/ * hw_cons_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ qed_chain_get_cons_idx (int /*<<< orphan*/ *) ; 

int qede_txq_has_work(struct qede_tx_queue *txq)
{
	u16 hw_bd_cons;

	/* Tell compiler that consumer and producer can change */
	barrier();
	hw_bd_cons = le16_to_cpu(*txq->hw_cons_ptr);
	if (qed_chain_get_cons_idx(&txq->tx_pbl) == hw_bd_cons + 1)
		return 0;

	return hw_bd_cons != qed_chain_get_cons_idx(&txq->tx_pbl);
}