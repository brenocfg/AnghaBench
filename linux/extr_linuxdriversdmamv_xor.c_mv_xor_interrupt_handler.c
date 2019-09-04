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
typedef  int u32 ;
struct mv_xor_chan {int /*<<< orphan*/  irq_tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int XOR_INTR_ERRORS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mv_chan_clear_eoc_cause (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  mv_chan_err_interrupt_handler (struct mv_xor_chan*,int) ; 
 int mv_chan_get_intr_cause (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  mv_chan_to_devp (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mv_xor_interrupt_handler(int irq, void *data)
{
	struct mv_xor_chan *chan = data;
	u32 intr_cause = mv_chan_get_intr_cause(chan);

	dev_dbg(mv_chan_to_devp(chan), "intr cause %x\n", intr_cause);

	if (intr_cause & XOR_INTR_ERRORS)
		mv_chan_err_interrupt_handler(chan, intr_cause);

	tasklet_schedule(&chan->irq_tasklet);

	mv_chan_clear_eoc_cause(chan);

	return IRQ_HANDLED;
}