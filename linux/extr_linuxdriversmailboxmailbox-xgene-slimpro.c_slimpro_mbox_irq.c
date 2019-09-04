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
struct slimpro_mbox_chan {int /*<<< orphan*/  rx_msg; int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ mb_chan_status_ack (struct slimpro_mbox_chan*) ; 
 scalar_t__ mb_chan_status_avail (struct slimpro_mbox_chan*) ; 
 int /*<<< orphan*/  mbox_chan_received_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_chan_txdone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t slimpro_mbox_irq(int irq, void *id)
{
	struct slimpro_mbox_chan *mb_chan = id;

	if (mb_chan_status_ack(mb_chan))
		mbox_chan_txdone(mb_chan->chan, 0);

	if (mb_chan_status_avail(mb_chan))
		mbox_chan_received_data(mb_chan->chan, mb_chan->rx_msg);

	return IRQ_HANDLED;
}