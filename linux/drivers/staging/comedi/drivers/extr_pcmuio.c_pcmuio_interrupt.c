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
struct pcmuio_private {int irq2; } ;
struct comedi_device {int irq; struct pcmuio_private* private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ pcmuio_handle_asic_interrupt (struct comedi_device*,int) ; 

__attribute__((used)) static irqreturn_t pcmuio_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct pcmuio_private *devpriv = dev->private;
	int handled = 0;

	if (irq == dev->irq)
		handled += pcmuio_handle_asic_interrupt(dev, 0);
	if (irq == devpriv->irq2)
		handled += pcmuio_handle_asic_interrupt(dev, 1);

	return handled ? IRQ_HANDLED : IRQ_NONE;
}