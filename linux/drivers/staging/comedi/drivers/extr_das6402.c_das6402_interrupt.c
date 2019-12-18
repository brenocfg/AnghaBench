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
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* read_subdev; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct comedi_async {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_OVERFLOW ; 
 unsigned int DAS6402_STATUS_FFNE ; 
 unsigned int DAS6402_STATUS_FFULL ; 
 unsigned int DAS6402_STATUS_INT ; 
 scalar_t__ DAS6402_STATUS_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned int*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int das6402_ai_read_sample (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  das6402_clear_all_interrupts (struct comedi_device*) ; 
 unsigned int inb (scalar_t__) ; 

__attribute__((used)) static irqreturn_t das6402_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int status;

	status = inb(dev->iobase + DAS6402_STATUS_REG);
	if ((status & DAS6402_STATUS_INT) == 0)
		return IRQ_NONE;

	if (status & DAS6402_STATUS_FFULL) {
		async->events |= COMEDI_CB_OVERFLOW;
	} else if (status & DAS6402_STATUS_FFNE) {
		unsigned int val;

		val = das6402_ai_read_sample(dev, s);
		comedi_buf_write_samples(s, &val, 1);

		if (cmd->stop_src == TRIG_COUNT &&
		    async->scans_done >= cmd->stop_arg)
			async->events |= COMEDI_CB_EOA;
	}

	das6402_clear_all_interrupts(dev);

	comedi_handle_events(dev, s);

	return IRQ_HANDLED;
}