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
struct comedi_device {int /*<<< orphan*/  class_dev; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DT2821_ADCSR_REG ; 
 scalar_t__ DT2821_CHANCSR_REG ; 
 scalar_t__ DT2821_DACSR_REG ; 
 int /*<<< orphan*/  DT2821_SUPCSR_BDINIT ; 
 scalar_t__ DT2821_SUPCSR_REG ; 
 scalar_t__ DT2821_TMRCTR_REG ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dt282x_initialize(struct comedi_device *dev)
{
	/* Initialize board */
	outw(DT2821_SUPCSR_BDINIT, dev->iobase + DT2821_SUPCSR_REG);
	inw(dev->iobase + DT2821_ADCSR_REG);

	/*
	 * At power up, some registers are in a well-known state.
	 * Check them to see if a DT2821 series board is present.
	 */
	if (((inw(dev->iobase + DT2821_ADCSR_REG) & 0xfff0) != 0x7c00) ||
	    ((inw(dev->iobase + DT2821_CHANCSR_REG) & 0xf0f0) != 0x70f0) ||
	    ((inw(dev->iobase + DT2821_DACSR_REG) & 0x7c93) != 0x7c90) ||
	    ((inw(dev->iobase + DT2821_SUPCSR_REG) & 0xf8ff) != 0x0000) ||
	    ((inw(dev->iobase + DT2821_TMRCTR_REG) & 0xff00) != 0xf000)) {
		dev_err(dev->class_dev, "board not found\n");
		return -EIO;
	}
	return 0;
}