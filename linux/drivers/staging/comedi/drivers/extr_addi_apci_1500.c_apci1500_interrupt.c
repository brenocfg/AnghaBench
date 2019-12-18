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
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* read_subdev; struct apci1500_private* private; } ;
struct apci1500_private {scalar_t__ amcc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 scalar_t__ APCI1500_Z8536_PORTB_REG ; 
 unsigned int INTCSR_INTR_ASSERTED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  Z8536_PA_CMDSTAT_REG ; 
 int /*<<< orphan*/  Z8536_PB_CMDSTAT_REG ; 
 scalar_t__ apci1500_ack_irq (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned int*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int inb (scalar_t__) ; 
 unsigned int inl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t apci1500_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct apci1500_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	unsigned int status = 0;
	unsigned int val;

	val = inl(devpriv->amcc + AMCC_OP_REG_INTCSR);
	if (!(val & INTCSR_INTR_ASSERTED))
		return IRQ_NONE;

	if (apci1500_ack_irq(dev, Z8536_PA_CMDSTAT_REG))
		status |= 0x01;	/* port a event (inputs 0-7) */

	if (apci1500_ack_irq(dev, Z8536_PB_CMDSTAT_REG)) {
		/* Tests if this is an external error */
		val = inb(dev->iobase + APCI1500_Z8536_PORTB_REG);
		val &= 0xc0;
		if (val) {
			if (val & 0x80)	/* voltage error */
				status |= 0x40;
			if (val & 0x40)	/* short circuit error */
				status |= 0x80;
		} else {
			status |= 0x02;	/* port b event (inputs 8-13) */
		}
	}

	/*
	 * NOTE: The 'status' returned by the sample matches the
	 * interrupt mask information from the APCI-1500 Users Manual.
	 *
	 *    Mask     Meaning
	 * ----------  ------------------------------------------
	 * 0x00000001  Event 1 has occurred
	 * 0x00000010  Event 2 has occurred
	 * 0x00000100  Counter/timer 1 has run down (not implemented)
	 * 0x00001000  Counter/timer 2 has run down (not implemented)
	 * 0x00010000  Counter 3 has run down (not implemented)
	 * 0x00100000  Watchdog has run down (not implemented)
	 * 0x01000000  Voltage error
	 * 0x10000000  Short-circuit error
	 */
	comedi_buf_write_samples(s, &status, 1);
	comedi_handle_events(dev, s);

	return IRQ_HANDLED;
}