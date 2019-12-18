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
typedef  scalar_t__ u32 ;
struct tx_ring {scalar_t__ used; struct tcb* send_head; int /*<<< orphan*/ * send_tail; } ;
struct tcb {struct tcb* next; } ;
struct et131x_adapter {int /*<<< orphan*/  tcb_send_qlock; struct tx_ring tx_ring; } ;

/* Variables and functions */
 scalar_t__ NUM_TCB ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  free_send_packet (struct et131x_adapter*,struct tcb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void et131x_free_busy_send_packets(struct et131x_adapter *adapter)
{
	struct tcb *tcb;
	unsigned long flags;
	u32 freed = 0;
	struct tx_ring *tx_ring = &adapter->tx_ring;

	/* Any packets being sent? Check the first TCB on the send list */
	spin_lock_irqsave(&adapter->tcb_send_qlock, flags);

	tcb = tx_ring->send_head;

	while (tcb != NULL && freed < NUM_TCB) {
		struct tcb *next = tcb->next;

		tx_ring->send_head = next;

		if (next == NULL)
			tx_ring->send_tail = NULL;

		tx_ring->used--;

		spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);

		freed++;
		free_send_packet(adapter, tcb);

		spin_lock_irqsave(&adapter->tcb_send_qlock, flags);

		tcb = tx_ring->send_head;
	}

	WARN_ON(freed == NUM_TCB);

	spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);

	tx_ring->used = 0;
}