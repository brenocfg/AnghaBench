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
 scalar_t__ APCI1032_CTRL_REG ; 
 scalar_t__ APCI1032_MODE1_REG ; 
 scalar_t__ APCI1032_MODE2_REG ; 
 scalar_t__ APCI1032_STATUS_REG ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static int apci1032_reset(struct comedi_device *dev)
{
	/* disable the interrupts */
	outl(0x0, dev->iobase + APCI1032_CTRL_REG);
	/* Reset the interrupt status register */
	inl(dev->iobase + APCI1032_STATUS_REG);
	/* Disable the and/or interrupt */
	outl(0x0, dev->iobase + APCI1032_MODE1_REG);
	outl(0x0, dev->iobase + APCI1032_MODE2_REG);

	return 0;
}