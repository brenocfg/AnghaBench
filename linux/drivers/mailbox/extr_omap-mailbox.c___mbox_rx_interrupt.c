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
typedef  int /*<<< orphan*/  u32 ;
struct omap_mbox_queue {int full; int /*<<< orphan*/  work; int /*<<< orphan*/  fifo; } ;
struct omap_mbox {struct omap_mbox_queue* rxq; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _omap_mbox_disable_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ack_mbox_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int kfifo_avail (int /*<<< orphan*/ *) ; 
 int kfifo_in (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  mbox_fifo_empty (struct omap_mbox*) ; 
 int /*<<< orphan*/  mbox_fifo_read (struct omap_mbox*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __mbox_rx_interrupt(struct omap_mbox *mbox)
{
	struct omap_mbox_queue *mq = mbox->rxq;
	u32 msg;
	int len;

	while (!mbox_fifo_empty(mbox)) {
		if (unlikely(kfifo_avail(&mq->fifo) < sizeof(msg))) {
			_omap_mbox_disable_irq(mbox, IRQ_RX);
			mq->full = true;
			goto nomem;
		}

		msg = mbox_fifo_read(mbox);

		len = kfifo_in(&mq->fifo, (unsigned char *)&msg, sizeof(msg));
		WARN_ON(len != sizeof(msg));
	}

	/* no more messages in the fifo. clear IRQ source. */
	ack_mbox_irq(mbox, IRQ_RX);
nomem:
	schedule_work(&mbox->rxq->work);
}