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
struct tx_ring {scalar_t__ used; struct tcb* tcb_qtail; struct tcb* tcb_qhead; } ;
struct tcb {struct tcb* next; struct sk_buff* skb; } ;
struct sk_buff {scalar_t__ len; } ;
struct et131x_adapter {int /*<<< orphan*/  tcb_ready_qlock; struct tx_ring tx_ring; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ ETH_HLEN ; 
 scalar_t__ NUM_TCB ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int nic_send_packet (struct et131x_adapter*,struct tcb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int send_packet(struct sk_buff *skb, struct et131x_adapter *adapter)
{
	int status;
	struct tcb *tcb;
	unsigned long flags;
	struct tx_ring *tx_ring = &adapter->tx_ring;

	/* All packets must have at least a MAC address and a protocol type */
	if (skb->len < ETH_HLEN)
		return -EIO;

	spin_lock_irqsave(&adapter->tcb_ready_qlock, flags);

	tcb = tx_ring->tcb_qhead;

	if (tcb == NULL) {
		spin_unlock_irqrestore(&adapter->tcb_ready_qlock, flags);
		return -ENOMEM;
	}

	tx_ring->tcb_qhead = tcb->next;

	if (tx_ring->tcb_qhead == NULL)
		tx_ring->tcb_qtail = NULL;

	spin_unlock_irqrestore(&adapter->tcb_ready_qlock, flags);

	tcb->skb = skb;
	tcb->next = NULL;

	status = nic_send_packet(adapter, tcb);

	if (status != 0) {
		spin_lock_irqsave(&adapter->tcb_ready_qlock, flags);

		if (tx_ring->tcb_qtail)
			tx_ring->tcb_qtail->next = tcb;
		else
			/* Apparently ready Q is empty. */
			tx_ring->tcb_qhead = tcb;

		tx_ring->tcb_qtail = tcb;
		spin_unlock_irqrestore(&adapter->tcb_ready_qlock, flags);
		return status;
	}
	WARN_ON(tx_ring->used > NUM_TCB);
	return 0;
}