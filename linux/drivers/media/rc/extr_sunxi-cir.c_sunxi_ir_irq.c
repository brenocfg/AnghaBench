#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sunxi_ir {unsigned int fifo_size; int /*<<< orphan*/  ir_lock; TYPE_1__* rc; scalar_t__ base; } ;
struct ir_raw_event {int pulse; unsigned char duration; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {unsigned char rx_resolution; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long REG_RXSTA_CLEARALL ; 
 unsigned int REG_RXSTA_GET_AC (unsigned long) ; 
 unsigned long REG_RXSTA_RA ; 
 unsigned long REG_RXSTA_ROI ; 
 unsigned long REG_RXSTA_RPE ; 
 scalar_t__ SUNXI_IR_RXFIFO_REG ; 
 scalar_t__ SUNXI_IR_RXSTA_REG ; 
 int /*<<< orphan*/  ir_raw_event_handle (TYPE_1__*) ; 
 int /*<<< orphan*/  ir_raw_event_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  ir_raw_event_set_idle (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ir_raw_event_store_with_filter (TYPE_1__*,struct ir_raw_event*) ; 
 unsigned char readb (scalar_t__) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sunxi_ir_irq(int irqno, void *dev_id)
{
	unsigned long status;
	unsigned char dt;
	unsigned int cnt, rc;
	struct sunxi_ir *ir = dev_id;
	struct ir_raw_event rawir = {};

	spin_lock(&ir->ir_lock);

	status = readl(ir->base + SUNXI_IR_RXSTA_REG);

	/* clean all pending statuses */
	writel(status | REG_RXSTA_CLEARALL, ir->base + SUNXI_IR_RXSTA_REG);

	if (status & (REG_RXSTA_RA | REG_RXSTA_RPE)) {
		/* How many messages in fifo */
		rc  = REG_RXSTA_GET_AC(status);
		/* Sanity check */
		rc = rc > ir->fifo_size ? ir->fifo_size : rc;
		/* If we have data */
		for (cnt = 0; cnt < rc; cnt++) {
			/* for each bit in fifo */
			dt = readb(ir->base + SUNXI_IR_RXFIFO_REG);
			rawir.pulse = (dt & 0x80) != 0;
			rawir.duration = ((dt & 0x7f) + 1) *
					 ir->rc->rx_resolution;
			ir_raw_event_store_with_filter(ir->rc, &rawir);
		}
	}

	if (status & REG_RXSTA_ROI) {
		ir_raw_event_reset(ir->rc);
	} else if (status & REG_RXSTA_RPE) {
		ir_raw_event_set_idle(ir->rc, true);
		ir_raw_event_handle(ir->rc);
	}

	spin_unlock(&ir->ir_lock);

	return IRQ_HANDLED;
}