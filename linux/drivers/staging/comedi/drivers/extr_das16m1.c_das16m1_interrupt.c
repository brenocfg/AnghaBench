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
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  attached; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DAS16M1_CLR_INTR_REG ; 
 int DAS16M1_CS_IRQDATA ; 
 int DAS16M1_CS_OVRUN ; 
 scalar_t__ DAS16M1_CS_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  das16m1_handler (struct comedi_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t das16m1_interrupt(int irq, void *d)
{
	int status;
	struct comedi_device *dev = d;

	if (!dev->attached) {
		dev_err(dev->class_dev, "premature interrupt\n");
		return IRQ_HANDLED;
	}
	/*  prevent race with comedi_poll() */
	spin_lock(&dev->spinlock);

	status = inb(dev->iobase + DAS16M1_CS_REG);

	if ((status & (DAS16M1_CS_IRQDATA | DAS16M1_CS_OVRUN)) == 0) {
		dev_err(dev->class_dev, "spurious interrupt\n");
		spin_unlock(&dev->spinlock);
		return IRQ_NONE;
	}

	das16m1_handler(dev, status);

	/* clear interrupt */
	outb(0, dev->iobase + DAS16M1_CLR_INTR_REG);

	spin_unlock(&dev->spinlock);
	return IRQ_HANDLED;
}