#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_7__ {int csr; int /*<<< orphan*/  lock; TYPE_1__* dma; } ;
typedef  TYPE_2__ avmcard ;
struct TYPE_6__ {int /*<<< orphan*/  send_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMCC_INTCSR ; 
 int EN_TX_TC_INT ; 
 int /*<<< orphan*/  b1dma_dispatch_tx (TYPE_2__*) ; 
 int /*<<< orphan*/  b1dma_writel (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void b1dma_queue_tx(avmcard *card, struct sk_buff *skb)
{
	unsigned long flags;

	spin_lock_irqsave(&card->lock, flags);

	skb_queue_tail(&card->dma->send_queue, skb);

	if (!(card->csr & EN_TX_TC_INT)) {
		b1dma_dispatch_tx(card);
		b1dma_writel(card, card->csr, AMCC_INTCSR);
	}

	spin_unlock_irqrestore(&card->lock, flags);
}