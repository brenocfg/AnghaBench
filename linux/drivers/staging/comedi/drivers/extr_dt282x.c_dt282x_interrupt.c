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
struct dt282x_private {scalar_t__ dma_dir; scalar_t__ nread; int supcsr; scalar_t__ ad_2scomp; } ;
struct comedi_subdevice {unsigned short maxdata; TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  attached; struct comedi_subdevice* write_subdev; struct comedi_subdevice* read_subdev; struct dt282x_private* private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 scalar_t__ COMEDI_ISADMA_READ ; 
 unsigned int DT2821_ADCSR_ADDONE ; 
 unsigned int DT2821_ADCSR_ADERR ; 
 scalar_t__ DT2821_ADCSR_REG ; 
 scalar_t__ DT2821_ADDAT_REG ; 
 unsigned int DT2821_DACSR_DAERR ; 
 scalar_t__ DT2821_DACSR_REG ; 
 unsigned int DT2821_SUPCSR_DMAD ; 
 scalar_t__ DT2821_SUPCSR_REG ; 
 unsigned int DT2821_SUPCSR_SCDN ; 
 int DT2821_SUPCSR_STRIG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned short comedi_offset_munge (struct comedi_subdevice*,unsigned short) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dt282x_ai_dma_interrupt (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dt282x_ao_dma_interrupt (struct comedi_device*,struct comedi_subdevice*) ; 
 void* inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t dt282x_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct dt282x_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_subdevice *s_ao = dev->write_subdev;
	unsigned int supcsr, adcsr, dacsr;
	int handled = 0;

	if (!dev->attached) {
		dev_err(dev->class_dev, "spurious interrupt\n");
		return IRQ_HANDLED;
	}

	adcsr = inw(dev->iobase + DT2821_ADCSR_REG);
	dacsr = inw(dev->iobase + DT2821_DACSR_REG);
	supcsr = inw(dev->iobase + DT2821_SUPCSR_REG);
	if (supcsr & DT2821_SUPCSR_DMAD) {
		if (devpriv->dma_dir == COMEDI_ISADMA_READ)
			dt282x_ai_dma_interrupt(dev, s);
		else
			dt282x_ao_dma_interrupt(dev, s_ao);
		handled = 1;
	}
	if (adcsr & DT2821_ADCSR_ADERR) {
		if (devpriv->nread != 0) {
			dev_err(dev->class_dev, "A/D error\n");
			s->async->events |= COMEDI_CB_ERROR;
		}
		handled = 1;
	}
	if (dacsr & DT2821_DACSR_DAERR) {
		dev_err(dev->class_dev, "D/A error\n");
		s_ao->async->events |= COMEDI_CB_ERROR;
		handled = 1;
	}
#if 0
	if (adcsr & DT2821_ADCSR_ADDONE) {
		unsigned short data;

		data = inw(dev->iobase + DT2821_ADDAT_REG);
		data &= s->maxdata;
		if (devpriv->ad_2scomp)
			data = comedi_offset_munge(s, data);

		comedi_buf_write_samples(s, &data, 1);

		devpriv->nread--;
		if (!devpriv->nread) {
			s->async->events |= COMEDI_CB_EOA;
		} else {
			if (supcsr & DT2821_SUPCSR_SCDN)
				outw(devpriv->supcsr | DT2821_SUPCSR_STRIG,
				     dev->iobase + DT2821_SUPCSR_REG);
		}
		handled = 1;
	}
#endif
	comedi_handle_events(dev, s);
	if (s_ao)
		comedi_handle_events(dev, s_ao);

	return IRQ_RETVAL(handled);
}