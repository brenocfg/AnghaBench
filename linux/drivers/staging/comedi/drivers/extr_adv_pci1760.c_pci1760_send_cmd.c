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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PCI1760_CMD_TIMEOUT ; 
 scalar_t__ PCI1760_IMB_REG (int) ; 
 scalar_t__ PCI1760_OMB_REG (int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int inb (scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci1760_send_cmd(struct comedi_device *dev,
			    unsigned char cmd, unsigned short val)
{
	unsigned long timeout;

	/* send the command and parameter */
	outb(val & 0xff, dev->iobase + PCI1760_OMB_REG(0));
	outb((val >> 8) & 0xff, dev->iobase + PCI1760_OMB_REG(1));
	outb(cmd, dev->iobase + PCI1760_OMB_REG(2));
	outb(0, dev->iobase + PCI1760_OMB_REG(3));

	/* datasheet says to allow up to 250 usec for the command to complete */
	timeout = jiffies + usecs_to_jiffies(PCI1760_CMD_TIMEOUT);
	do {
		if (inb(dev->iobase + PCI1760_IMB_REG(2)) == cmd) {
			/* command success; return the feedback data */
			return inb(dev->iobase + PCI1760_IMB_REG(0)) |
			       (inb(dev->iobase + PCI1760_IMB_REG(1)) << 8);
		}
		cpu_relax();
	} while (time_before(jiffies, timeout));

	return -EBUSY;
}