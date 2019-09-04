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
struct altera_mbox {int intr_mode; int /*<<< orphan*/  rxpoll_timer; struct mbox_chan* chan; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  MBOX_POLLING_MS ; 
 int /*<<< orphan*/  altera_mbox_poll_rx ; 
 int /*<<< orphan*/  altera_mbox_rx_interrupt ; 
 int /*<<< orphan*/  altera_mbox_rx_intmask (struct altera_mbox*,int) ; 
 scalar_t__ jiffies ; 
 struct altera_mbox* mbox_chan_to_altera_mbox (struct mbox_chan*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbox_chan*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int altera_mbox_startup_receiver(struct mbox_chan *chan)
{
	int ret;
	struct altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);

	if (mbox->intr_mode) {
		ret = request_irq(mbox->irq, altera_mbox_rx_interrupt, 0,
				  DRIVER_NAME, chan);
		if (unlikely(ret)) {
			mbox->intr_mode = false;
			goto polling; /* use polling if failed */
		}

		altera_mbox_rx_intmask(mbox, true);
		return 0;
	}

polling:
	/* Setup polling timer */
	mbox->chan = chan;
	timer_setup(&mbox->rxpoll_timer, altera_mbox_poll_rx, 0);
	mod_timer(&mbox->rxpoll_timer,
		  jiffies + msecs_to_jiffies(MBOX_POLLING_MS));

	return 0;
}