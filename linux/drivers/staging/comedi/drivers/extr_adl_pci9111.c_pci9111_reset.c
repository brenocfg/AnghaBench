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
struct pci9111_private_data {int /*<<< orphan*/  lcr_io_base; } ;
struct comedi_device {scalar_t__ iobase; struct pci9111_private_data* private; } ;

/* Variables and functions */
 scalar_t__ PCI9111_AI_TRIG_CTRL_REG ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  plx9050_interrupt_control (int /*<<< orphan*/ ,int,int,int,int,int) ; 

__attribute__((used)) static int pci9111_reset(struct comedi_device *dev)
{
	struct pci9111_private_data *dev_private = dev->private;

	/*  Set trigger source to software */
	plx9050_interrupt_control(dev_private->lcr_io_base, true, true, true,
				  true, false);

	/* disable A/D triggers (software trigger mode) and auto scan off */
	outb(0, dev->iobase + PCI9111_AI_TRIG_CTRL_REG);

	return 0;
}