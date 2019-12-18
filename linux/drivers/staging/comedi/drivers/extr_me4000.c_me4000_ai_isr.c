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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  attached; struct comedi_subdevice* read_subdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int ME4000_AI_CTRL_HF_IRQ_RESET ; 
 scalar_t__ ME4000_AI_CTRL_REG ; 
 unsigned int ME4000_AI_CTRL_SC_IRQ_RESET ; 
 int ME4000_AI_FIFO_COUNT ; 
 unsigned int ME4000_AI_STATUS_EF_DATA ; 
 unsigned int ME4000_AI_STATUS_FF_DATA ; 
 unsigned int ME4000_AI_STATUS_HF_DATA ; 
 scalar_t__ ME4000_AI_STATUS_REG ; 
 int ME4000_IRQ_STATUS_AI_HF ; 
 scalar_t__ ME4000_IRQ_STATUS_REG ; 
 int ME4000_IRQ_STATUS_SC ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned int*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int inl (scalar_t__) ; 
 unsigned int me4000_ai_get_sample (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t me4000_ai_isr(int irq, void *dev_id)
{
	unsigned int tmp;
	struct comedi_device *dev = dev_id;
	struct comedi_subdevice *s = dev->read_subdev;
	int i;
	int c = 0;
	unsigned int lval;

	if (!dev->attached)
		return IRQ_NONE;

	if (inl(dev->iobase + ME4000_IRQ_STATUS_REG) &
	    ME4000_IRQ_STATUS_AI_HF) {
		/* Read status register to find out what happened */
		tmp = inl(dev->iobase + ME4000_AI_STATUS_REG);

		if (!(tmp & ME4000_AI_STATUS_FF_DATA) &&
		    !(tmp & ME4000_AI_STATUS_HF_DATA) &&
		    (tmp & ME4000_AI_STATUS_EF_DATA)) {
			dev_err(dev->class_dev, "FIFO overflow\n");
			s->async->events |= COMEDI_CB_ERROR;
			c = ME4000_AI_FIFO_COUNT;
		} else if ((tmp & ME4000_AI_STATUS_FF_DATA) &&
			   !(tmp & ME4000_AI_STATUS_HF_DATA) &&
			   (tmp & ME4000_AI_STATUS_EF_DATA)) {
			c = ME4000_AI_FIFO_COUNT / 2;
		} else {
			dev_err(dev->class_dev, "Undefined FIFO state\n");
			s->async->events |= COMEDI_CB_ERROR;
			c = 0;
		}

		for (i = 0; i < c; i++) {
			lval = me4000_ai_get_sample(dev, s);
			if (!comedi_buf_write_samples(s, &lval, 1))
				break;
		}

		/* Work is done, so reset the interrupt */
		tmp |= ME4000_AI_CTRL_HF_IRQ_RESET;
		outl(tmp, dev->iobase + ME4000_AI_CTRL_REG);
		tmp &= ~ME4000_AI_CTRL_HF_IRQ_RESET;
		outl(tmp, dev->iobase + ME4000_AI_CTRL_REG);
	}

	if (inl(dev->iobase + ME4000_IRQ_STATUS_REG) &
	    ME4000_IRQ_STATUS_SC) {
		/* Acquisition is complete */
		s->async->events |= COMEDI_CB_EOA;

		/* Poll data until fifo empty */
		while (inl(dev->iobase + ME4000_AI_STATUS_REG) &
		       ME4000_AI_STATUS_EF_DATA) {
			lval = me4000_ai_get_sample(dev, s);
			if (!comedi_buf_write_samples(s, &lval, 1))
				break;
		}

		/* Work is done, so reset the interrupt */
		tmp = inl(dev->iobase + ME4000_AI_CTRL_REG);
		tmp |= ME4000_AI_CTRL_SC_IRQ_RESET;
		outl(tmp, dev->iobase + ME4000_AI_CTRL_REG);
		tmp &= ~ME4000_AI_CTRL_SC_IRQ_RESET;
		outl(tmp, dev->iobase + ME4000_AI_CTRL_REG);
	}

	comedi_handle_events(dev, s);

	return IRQ_HANDLED;
}