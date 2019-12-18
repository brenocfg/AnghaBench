#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct omap_mbox_queue {struct omap_mbox* mbox; } ;
struct omap_mbox {struct omap_mbox_queue* rxq; TYPE_1__* chan; scalar_t__ send_no_irq; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  txdone_method; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_RX ; 
 int /*<<< orphan*/  TXDONE_BY_ACK ; 
 int /*<<< orphan*/  _omap_mbox_enable_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_interrupt ; 
 struct omap_mbox_queue* mbox_queue_alloc (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_queue_free (struct omap_mbox_queue*) ; 
 int /*<<< orphan*/  mbox_rx_work ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct omap_mbox*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int omap_mbox_startup(struct omap_mbox *mbox)
{
	int ret = 0;
	struct omap_mbox_queue *mq;

	mq = mbox_queue_alloc(mbox, mbox_rx_work);
	if (!mq)
		return -ENOMEM;
	mbox->rxq = mq;
	mq->mbox = mbox;

	ret = request_irq(mbox->irq, mbox_interrupt, IRQF_SHARED,
			  mbox->name, mbox);
	if (unlikely(ret)) {
		pr_err("failed to register mailbox interrupt:%d\n", ret);
		goto fail_request_irq;
	}

	if (mbox->send_no_irq)
		mbox->chan->txdone_method = TXDONE_BY_ACK;

	_omap_mbox_enable_irq(mbox, IRQ_RX);

	return 0;

fail_request_irq:
	mbox_queue_free(mbox->rxq);
	return ret;
}