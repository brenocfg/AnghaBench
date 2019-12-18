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
 unsigned int CLEAR_INTR_MASK ; 
 scalar_t__ DAS1800_STATUS ; 
 unsigned int INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  das1800_ai_handler (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t das1800_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	unsigned int status;

	if (!dev->attached) {
		dev_err(dev->class_dev, "premature interrupt\n");
		return IRQ_HANDLED;
	}

	/*
	 * Protects the indirect addressing selected by DAS1800_SELECT
	 * in das1800_ai_handler() also prevents race with das1800_ai_poll().
	 */
	spin_lock(&dev->spinlock);

	status = inb(dev->iobase + DAS1800_STATUS);

	/* if interrupt was not caused by das-1800 */
	if (!(status & INT)) {
		spin_unlock(&dev->spinlock);
		return IRQ_NONE;
	}
	/* clear the interrupt status bit INT */
	outb(CLEAR_INTR_MASK & ~INT, dev->iobase + DAS1800_STATUS);
	/*  handle interrupt */
	das1800_ai_handler(dev);

	spin_unlock(&dev->spinlock);
	return IRQ_HANDLED;
}