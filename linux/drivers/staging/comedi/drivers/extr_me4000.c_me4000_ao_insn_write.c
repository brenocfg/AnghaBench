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
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int ME4000_AO_CTRL_IMMEDIATE_STOP ; 
 scalar_t__ ME4000_AO_CTRL_REG (unsigned int) ; 
 scalar_t__ ME4000_AO_SINGLE_REG (unsigned int) ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static int me4000_ao_insn_write(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int tmp;

	/* Stop any running conversion */
	tmp = inl(dev->iobase + ME4000_AO_CTRL_REG(chan));
	tmp |= ME4000_AO_CTRL_IMMEDIATE_STOP;
	outl(tmp, dev->iobase + ME4000_AO_CTRL_REG(chan));

	/* Clear control register and set to single mode */
	outl(0x0, dev->iobase + ME4000_AO_CTRL_REG(chan));

	/* Write data value */
	outl(data[0], dev->iobase + ME4000_AO_SINGLE_REG(chan));

	/* Store in the mirror */
	s->readback[chan] = data[0];

	return 1;
}