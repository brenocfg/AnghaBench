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
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  class_dev; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct TYPE_2__ {scalar_t__ scans_done; int /*<<< orphan*/  events; int /*<<< orphan*/  cur_chan; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 scalar_t__ PCI171X_CLRINT_REG ; 
 unsigned int PCI171X_STATUS_FE ; 
 unsigned int PCI171X_STATUS_FF ; 
 scalar_t__ PCI171X_STATUS_REG ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned int*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int pci1710_ai_read_sample (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void pci1710_handle_every_sample(struct comedi_device *dev,
					struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int status;
	unsigned int val;
	int ret;

	status = inw(dev->iobase + PCI171X_STATUS_REG);
	if (status & PCI171X_STATUS_FE) {
		dev_dbg(dev->class_dev, "A/D FIFO empty (%4x)\n", status);
		s->async->events |= COMEDI_CB_ERROR;
		return;
	}
	if (status & PCI171X_STATUS_FF) {
		dev_dbg(dev->class_dev,
			"A/D FIFO Full status (Fatal Error!) (%4x)\n", status);
		s->async->events |= COMEDI_CB_ERROR;
		return;
	}

	outb(0, dev->iobase + PCI171X_CLRINT_REG);

	for (; !(inw(dev->iobase + PCI171X_STATUS_REG) & PCI171X_STATUS_FE);) {
		ret = pci1710_ai_read_sample(dev, s, s->async->cur_chan, &val);
		if (ret) {
			s->async->events |= COMEDI_CB_ERROR;
			break;
		}

		comedi_buf_write_samples(s, &val, 1);

		if (cmd->stop_src == TRIG_COUNT &&
		    s->async->scans_done >= cmd->stop_arg) {
			s->async->events |= COMEDI_CB_EOA;
			break;
		}
	}

	outb(0, dev->iobase + PCI171X_CLRINT_REG);
}