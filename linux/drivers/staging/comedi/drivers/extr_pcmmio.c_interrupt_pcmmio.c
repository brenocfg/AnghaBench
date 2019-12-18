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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* read_subdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PCMMIO_INT_PENDING_REG ; 
 int /*<<< orphan*/  PCMMIO_PAGE_INT_ID ; 
 int inb (scalar_t__) ; 
 unsigned int pcmmio_dio_read (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmmio_dio_write (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmmio_handle_dio_intr (struct comedi_device*,struct comedi_subdevice*,unsigned int) ; 

__attribute__((used)) static irqreturn_t interrupt_pcmmio(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->read_subdev;
	unsigned int triggered;
	unsigned char int_pend;

	/* are there any interrupts pending */
	int_pend = inb(dev->iobase + PCMMIO_INT_PENDING_REG) & 0x07;
	if (!int_pend)
		return IRQ_NONE;

	/* get, and clear, the pending interrupts */
	triggered = pcmmio_dio_read(dev, PCMMIO_PAGE_INT_ID, 0);
	pcmmio_dio_write(dev, 0, PCMMIO_PAGE_INT_ID, 0);

	pcmmio_handle_dio_intr(dev, s, triggered);

	return IRQ_HANDLED;
}