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
struct dt282x_private {int supcsr; struct comedi_isadma* dma; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_isadma_desc {int /*<<< orphan*/  chan; } ;
struct comedi_isadma {size_t cur_dma; struct comedi_isadma_desc* desc; } ;
struct comedi_device {scalar_t__ iobase; struct dt282x_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_OVERFLOW ; 
 int DT2821_SUPCSR_CLRDMADNE ; 
 scalar_t__ DT2821_SUPCSR_REG ; 
 int /*<<< orphan*/  comedi_isadma_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt282x_ao_setup_dma (struct comedi_device*,struct comedi_subdevice*,size_t) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void dt282x_ao_dma_interrupt(struct comedi_device *dev,
				    struct comedi_subdevice *s)
{
	struct dt282x_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];

	outw(devpriv->supcsr | DT2821_SUPCSR_CLRDMADNE,
	     dev->iobase + DT2821_SUPCSR_REG);

	comedi_isadma_disable(desc->chan);

	if (!dt282x_ao_setup_dma(dev, s, dma->cur_dma))
		s->async->events |= COMEDI_CB_OVERFLOW;

	dma->cur_dma = 1 - dma->cur_dma;
}