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
struct omap_mbox {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TX ; 
 int /*<<< orphan*/  _omap_mbox_disable_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ack_mbox_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_chan_txdone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mbox_tx_interrupt(struct omap_mbox *mbox)
{
	_omap_mbox_disable_irq(mbox, IRQ_TX);
	ack_mbox_irq(mbox, IRQ_TX);
	mbox_chan_txdone(mbox->chan, 0);
}