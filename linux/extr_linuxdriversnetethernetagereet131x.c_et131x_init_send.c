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
struct tx_ring {int /*<<< orphan*/ * send_tail; int /*<<< orphan*/ * send_head; struct tcb* tcb_qtail; struct tcb* tcb_qhead; struct tcb* tcb_ring; } ;
struct tcb {struct tcb* next; } ;
struct et131x_adapter {struct tx_ring tx_ring; } ;

/* Variables and functions */
 int NUM_TCB ; 
 int /*<<< orphan*/  memset (struct tcb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void et131x_init_send(struct et131x_adapter *adapter)
{
	int i;
	struct tx_ring *tx_ring = &adapter->tx_ring;
	struct tcb *tcb = tx_ring->tcb_ring;

	tx_ring->tcb_qhead = tcb;

	memset(tcb, 0, sizeof(struct tcb) * NUM_TCB);

	for (i = 0; i < NUM_TCB; i++) {
		tcb->next = tcb + 1;
		tcb++;
	}

	tcb--;
	tx_ring->tcb_qtail = tcb;
	tcb->next = NULL;
	/* Curr send queue should now be empty */
	tx_ring->send_head = NULL;
	tx_ring->send_tail = NULL;
}