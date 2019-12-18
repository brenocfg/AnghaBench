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
struct mbox_chan {int dummy; } ;
struct altera_mbox {int /*<<< orphan*/  rxpoll_timer; int /*<<< orphan*/  is_sender; int /*<<< orphan*/  irq; scalar_t__ mbox_base; scalar_t__ intr_mode; } ;

/* Variables and functions */
 scalar_t__ MAILBOX_INTMASK_REG ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mbox_chan*) ; 
 struct altera_mbox* mbox_chan_to_altera_mbox (struct mbox_chan*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void altera_mbox_shutdown(struct mbox_chan *chan)
{
	struct altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);

	if (mbox->intr_mode) {
		/* Unmask all interrupt masks */
		writel_relaxed(~0, mbox->mbox_base + MAILBOX_INTMASK_REG);
		free_irq(mbox->irq, chan);
	} else if (!mbox->is_sender) {
		del_timer_sync(&mbox->rxpoll_timer);
	}
}