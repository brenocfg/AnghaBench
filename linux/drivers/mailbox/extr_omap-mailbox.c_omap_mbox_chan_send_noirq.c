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
struct omap_mbox {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IRQ_RX ; 
 int /*<<< orphan*/  _omap_mbox_disable_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _omap_mbox_enable_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ack_mbox_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_fifo_full (struct omap_mbox*) ; 
 int /*<<< orphan*/  mbox_fifo_read (struct omap_mbox*) ; 
 int /*<<< orphan*/  mbox_fifo_write (struct omap_mbox*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_mbox_chan_send_noirq(struct omap_mbox *mbox, u32 msg)
{
	int ret = -EBUSY;

	if (!mbox_fifo_full(mbox)) {
		_omap_mbox_enable_irq(mbox, IRQ_RX);
		mbox_fifo_write(mbox, msg);
		ret = 0;
		_omap_mbox_disable_irq(mbox, IRQ_RX);

		/* we must read and ack the interrupt directly from here */
		mbox_fifo_read(mbox);
		ack_mbox_irq(mbox, IRQ_RX);
	}

	return ret;
}