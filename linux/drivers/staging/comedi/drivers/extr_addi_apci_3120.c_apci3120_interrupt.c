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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  class_dev; struct comedi_subdevice* read_subdev; struct apci3120_private* private; } ;
struct comedi_cmd {int chanlist_len; scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct comedi_async {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;
struct apci3120_private {int ctrl; int mode; scalar_t__ amcc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int AINT_INT_MASK ; 
 unsigned int AINT_WT_COMPLETE ; 
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 unsigned int ANY_S593X_INT ; 
 scalar_t__ APCI3120_AI_FIFO_REG ; 
 int APCI3120_CTRL_EXT_TRIG ; 
 int APCI3120_MODE_EOS_IRQ_ENA ; 
 scalar_t__ APCI3120_MODE_REG ; 
 unsigned int APCI3120_STATUS_AMCC_INT ; 
 unsigned int APCI3120_STATUS_EOS_INT ; 
 unsigned int APCI3120_STATUS_INT_MASK ; 
 scalar_t__ APCI3120_STATUS_REG ; 
 unsigned int APCI3120_STATUS_TIMER2_INT ; 
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int MASTER_ABORT_INT ; 
 unsigned int TARGET_ABORT_INT ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  apci3120_clr_timer2_interrupt (struct comedi_device*) ; 
 int /*<<< orphan*/  apci3120_exttrig_enable (struct comedi_device*,int) ; 
 int /*<<< orphan*/  apci3120_interrupt_dma (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int inl (scalar_t__) ; 
 void* inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t apci3120_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct apci3120_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int status;
	unsigned int int_amcc;

	status = inw(dev->iobase + APCI3120_STATUS_REG);
	int_amcc = inl(devpriv->amcc + AMCC_OP_REG_INTCSR);

	if (!(status & APCI3120_STATUS_INT_MASK) &&
	    !(int_amcc & ANY_S593X_INT)) {
		dev_err(dev->class_dev, "IRQ from unknown source\n");
		return IRQ_NONE;
	}

	outl(int_amcc | AINT_INT_MASK, devpriv->amcc + AMCC_OP_REG_INTCSR);

	if (devpriv->ctrl & APCI3120_CTRL_EXT_TRIG)
		apci3120_exttrig_enable(dev, false);

	if (int_amcc & MASTER_ABORT_INT)
		dev_err(dev->class_dev, "AMCC IRQ - MASTER DMA ABORT!\n");
	if (int_amcc & TARGET_ABORT_INT)
		dev_err(dev->class_dev, "AMCC IRQ - TARGET DMA ABORT!\n");

	if ((status & APCI3120_STATUS_EOS_INT) &&
	    (devpriv->mode & APCI3120_MODE_EOS_IRQ_ENA)) {
		unsigned short val;
		int i;

		for (i = 0; i < cmd->chanlist_len; i++) {
			val = inw(dev->iobase + APCI3120_AI_FIFO_REG);
			comedi_buf_write_samples(s, &val, 1);
		}

		devpriv->mode |= APCI3120_MODE_EOS_IRQ_ENA;
		outb(devpriv->mode, dev->iobase + APCI3120_MODE_REG);
	}

	if (status & APCI3120_STATUS_TIMER2_INT) {
		/*
		 * for safety...
		 * timer2 interrupts are not enabled in the driver
		 */
		apci3120_clr_timer2_interrupt(dev);
	}

	if (status & APCI3120_STATUS_AMCC_INT) {
		/* AMCC- Clear write complete interrupt (DMA) */
		outl(AINT_WT_COMPLETE, devpriv->amcc + AMCC_OP_REG_INTCSR);

		/* do some data transfer */
		apci3120_interrupt_dma(dev, s);
	}

	if (cmd->stop_src == TRIG_COUNT && async->scans_done >= cmd->stop_arg)
		async->events |= COMEDI_CB_EOA;

	comedi_handle_events(dev, s);

	return IRQ_HANDLED;
}