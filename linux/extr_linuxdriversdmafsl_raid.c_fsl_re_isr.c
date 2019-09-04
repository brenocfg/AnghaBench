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
struct fsl_re_chan {int /*<<< orphan*/  irqtask; TYPE_1__* jrregs; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  jr_interrupt_status; int /*<<< orphan*/  jr_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_RE_CLR_INTR ; 
 int FSL_RE_ERROR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 struct fsl_re_chan* dev_get_drvdata (struct device*) ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t fsl_re_isr(int irq, void *data)
{
	struct fsl_re_chan *re_chan;
	u32 irqstate, status;

	re_chan = dev_get_drvdata((struct device *)data);

	irqstate = in_be32(&re_chan->jrregs->jr_interrupt_status);
	if (!irqstate)
		return IRQ_NONE;

	/*
	 * There's no way in upper layer (read MD layer) to recover from
	 * error conditions except restart everything. In long term we
	 * need to do something more than just crashing
	 */
	if (irqstate & FSL_RE_ERROR) {
		status = in_be32(&re_chan->jrregs->jr_status);
		dev_err(re_chan->dev, "chan error irqstate: %x, status: %x\n",
			irqstate, status);
	}

	/* Clear interrupt */
	out_be32(&re_chan->jrregs->jr_interrupt_status, FSL_RE_CLR_INTR);

	tasklet_schedule(&re_chan->irqtask);

	return IRQ_HANDLED;
}