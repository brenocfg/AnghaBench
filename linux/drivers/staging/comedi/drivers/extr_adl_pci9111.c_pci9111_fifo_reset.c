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
struct comedi_device {unsigned long iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI9111_INT_CTRL_FFEN ; 
 unsigned long PCI9111_INT_CTRL_REG ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void pci9111_fifo_reset(struct comedi_device *dev)
{
	unsigned long int_ctrl_reg = dev->iobase + PCI9111_INT_CTRL_REG;

	/* To reset the FIFO, set FFEN sequence as 0 -> 1 -> 0 */
	outb(0, int_ctrl_reg);
	outb(PCI9111_INT_CTRL_FFEN, int_ctrl_reg);
	outb(0, int_ctrl_reg);
}