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
struct netfront_queue {int /*<<< orphan*/  tx_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xennet_tx_buf_gc (struct netfront_queue*) ; 

__attribute__((used)) static irqreturn_t xennet_tx_interrupt(int irq, void *dev_id)
{
	struct netfront_queue *queue = dev_id;
	unsigned long flags;

	spin_lock_irqsave(&queue->tx_lock, flags);
	xennet_tx_buf_gc(queue);
	spin_unlock_irqrestore(&queue->tx_lock, flags);

	return IRQ_HANDLED;
}