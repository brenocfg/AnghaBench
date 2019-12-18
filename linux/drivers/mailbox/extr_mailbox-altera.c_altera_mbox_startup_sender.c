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
struct altera_mbox {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; scalar_t__ intr_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  altera_mbox_tx_interrupt ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct altera_mbox* mbox_chan_to_altera_mbox (struct mbox_chan*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbox_chan*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int altera_mbox_startup_sender(struct mbox_chan *chan)
{
	int ret;
	struct altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);

	if (mbox->intr_mode) {
		ret = request_irq(mbox->irq, altera_mbox_tx_interrupt, 0,
				  DRIVER_NAME, chan);
		if (unlikely(ret)) {
			dev_err(mbox->dev,
				"failed to register mailbox interrupt:%d\n",
				ret);
			return ret;
		}
	}

	return 0;
}