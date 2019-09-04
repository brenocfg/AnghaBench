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
typedef  int u32 ;
struct bcm2708_i2c {int error; int /*<<< orphan*/  lock; int /*<<< orphan*/  done; scalar_t__ nmsgs; TYPE_1__* msg; scalar_t__ pos; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSC_S ; 
 int BSC_S_CLKT ; 
 int BSC_S_DONE ; 
 int BSC_S_ERR ; 
 int BSC_S_RXR ; 
 int BSC_S_TXW ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  bcm2708_bsc_fifo_drain (struct bcm2708_i2c*) ; 
 int /*<<< orphan*/  bcm2708_bsc_fifo_fill (struct bcm2708_i2c*) ; 
 int /*<<< orphan*/  bcm2708_bsc_reset (struct bcm2708_i2c*) ; 
 int bcm2708_bsc_setup (struct bcm2708_i2c*) ; 
 int bcm2708_rd (struct bcm2708_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bcm2708_i2c_interrupt(int irq, void *dev_id)
{
	struct bcm2708_i2c *bi = dev_id;
	bool handled = true;
	u32 s;
	int ret;

	spin_lock(&bi->lock);

	/* we may see camera interrupts on the "other" I2C channel
		   Just return if we've not sent anything */
	if (!bi->nmsgs || !bi->msg) {
		goto early_exit;
	}

	s = bcm2708_rd(bi, BSC_S);

	if (s & (BSC_S_CLKT | BSC_S_ERR)) {
		bcm2708_bsc_reset(bi);
		bi->error = true;

		bi->msg = 0; /* to inform the that all work is done */
		bi->nmsgs = 0;
		/* wake up our bh */
		complete(&bi->done);
	} else if (s & BSC_S_DONE) {
		bi->nmsgs--;

		if (bi->msg->flags & I2C_M_RD) {
			bcm2708_bsc_fifo_drain(bi);
		}

		bcm2708_bsc_reset(bi);

		if (bi->nmsgs) {
			/* advance to next message */
			bi->msg++;
			bi->pos = 0;
			ret = bcm2708_bsc_setup(bi);
			if (ret < 0) {
				bcm2708_bsc_reset(bi);
				bi->error = true;
				bi->msg = 0; /* to inform the that all work is done */
				bi->nmsgs = 0;
				/* wake up our bh */
				complete(&bi->done);
				goto early_exit;
			}
		} else {
			bi->msg = 0; /* to inform the that all work is done */
			bi->nmsgs = 0;
			/* wake up our bh */
			complete(&bi->done);
		}
	} else if (s & BSC_S_TXW) {
		bcm2708_bsc_fifo_fill(bi);
	} else if (s & BSC_S_RXR) {
		bcm2708_bsc_fifo_drain(bi);
	} else {
		handled = false;
	}

early_exit:
	spin_unlock(&bi->lock);

	return handled ? IRQ_HANDLED : IRQ_NONE;
}