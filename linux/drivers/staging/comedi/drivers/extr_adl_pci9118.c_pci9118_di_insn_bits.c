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
 scalar_t__ PCI9118_DIO_REG ; 
 int inl (scalar_t__) ; 

__attribute__((used)) static int pci9118_di_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	/*
	 * The digital inputs and outputs share the read register.
	 * bits [7:4] are the digital outputs
	 * bits [3:0] are the digital inputs
	 */
	data[1] = inl(dev->iobase + PCI9118_DIO_REG) & 0xf;

	return insn->n;
}