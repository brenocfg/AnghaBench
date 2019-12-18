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
struct comedi_insn {int n; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ PCI6208_DIO ; 
 unsigned int PCI6208_DIO_DI_MASK ; 
 unsigned int PCI6208_DIO_DI_SHIFT ; 
 unsigned int inw (scalar_t__) ; 

__attribute__((used)) static int pci6208_di_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int val;

	val = inw(dev->iobase + PCI6208_DIO);
	val = (val & PCI6208_DIO_DI_MASK) >> PCI6208_DIO_DI_SHIFT;

	data[1] = val;

	return insn->n;
}