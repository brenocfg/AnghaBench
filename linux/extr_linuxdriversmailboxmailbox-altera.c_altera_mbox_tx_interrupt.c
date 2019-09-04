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
struct altera_mbox {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  altera_mbox_tx_intmask (struct altera_mbox*,int) ; 
 struct altera_mbox* mbox_chan_to_altera_mbox (struct mbox_chan*) ; 
 int /*<<< orphan*/  mbox_chan_txdone (struct mbox_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t altera_mbox_tx_interrupt(int irq, void *p)
{
	struct mbox_chan *chan = (struct mbox_chan *)p;
	struct altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);

	altera_mbox_tx_intmask(mbox, false);
	mbox_chan_txdone(chan, 0);

	return IRQ_HANDLED;
}