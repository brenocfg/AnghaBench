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
struct ni_660x_private {int /*<<< orphan*/  interrupt_lock; } ;
struct comedi_subdevice {scalar_t__ type; } ;
struct comedi_device {unsigned int n_subdevices; struct comedi_subdevice* subdevices; int /*<<< orphan*/  attached; struct ni_660x_private* private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ COMEDI_SUBD_COUNTER ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ni_660x_handle_gpct_interrupt (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t ni_660x_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct ni_660x_private *devpriv = dev->private;
	struct comedi_subdevice *s;
	unsigned int i;
	unsigned long flags;

	if (!dev->attached)
		return IRQ_NONE;
	/* make sure dev->attached is checked before doing anything else */
	smp_mb();

	/* lock to avoid race with comedi_poll */
	spin_lock_irqsave(&devpriv->interrupt_lock, flags);
	for (i = 0; i < dev->n_subdevices; ++i) {
		s = &dev->subdevices[i];
		if (s->type == COMEDI_SUBD_COUNTER)
			ni_660x_handle_gpct_interrupt(dev, s);
	}
	spin_unlock_irqrestore(&devpriv->interrupt_lock, flags);
	return IRQ_HANDLED;
}