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
struct rti800_private {scalar_t__* dac_2comp; } ;
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct rti800_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int RTI800_DAC0HI ; 
 int RTI800_DAC0LO ; 
 int RTI800_DAC1HI ; 
 int RTI800_DAC1LO ; 
 unsigned int comedi_offset_munge (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int rti800_ao_insn_write(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct rti800_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	int reg_lo = chan ? RTI800_DAC1LO : RTI800_DAC0LO;
	int reg_hi = chan ? RTI800_DAC1HI : RTI800_DAC0HI;
	int i;

	for (i = 0; i < insn->n; i++) {
		unsigned int val = data[i];

		s->readback[chan] = val;

		if (devpriv->dac_2comp[chan])
			val = comedi_offset_munge(s, val);

		outb(val & 0xff, dev->iobase + reg_lo);
		outb((val >> 8) & 0xff, dev->iobase + reg_hi);
	}

	return insn->n;
}