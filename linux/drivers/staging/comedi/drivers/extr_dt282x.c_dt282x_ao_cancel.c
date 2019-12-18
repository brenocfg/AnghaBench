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
struct dt282x_private {int dacsr; int supcsr; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; struct dt282x_private* private; } ;

/* Variables and functions */
 int DT2821_DACSR_HBOE ; 
 int DT2821_DACSR_LBOE ; 
 scalar_t__ DT2821_DACSR_REG ; 
 int DT2821_SUPCSR_DACINIT ; 
 scalar_t__ DT2821_SUPCSR_REG ; 
 int /*<<< orphan*/  dt282x_disable_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int dt282x_ao_cancel(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct dt282x_private *devpriv = dev->private;

	dt282x_disable_dma(dev);

	/* clear all bits but the DIO direction bits */
	devpriv->dacsr &= (DT2821_DACSR_LBOE | DT2821_DACSR_HBOE);

	outw(devpriv->dacsr, dev->iobase + DT2821_DACSR_REG);

	devpriv->supcsr = 0;
	outw(devpriv->supcsr | DT2821_SUPCSR_DACINIT,
	     dev->iobase + DT2821_SUPCSR_REG);

	return 0;
}