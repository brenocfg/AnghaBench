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
 int DMM32AT_CTRL_PAGE_8255 ; 
 scalar_t__ DMM32AT_CTRL_REG ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int dmm32at_8255_io(struct comedi_device *dev,
			   int dir, int port, int data, unsigned long regbase)
{
	/* get access to the DIO regs */
	outb(DMM32AT_CTRL_PAGE_8255, dev->iobase + DMM32AT_CTRL_REG);

	if (dir) {
		outb(data, dev->iobase + regbase + port);
		return 0;
	}
	return inb(dev->iobase + regbase + port);
}