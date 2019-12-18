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
struct rti802_private {scalar_t__* dac_coding; } ;
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct rti802_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ RTI802_DATAHIGH ; 
 scalar_t__ RTI802_DATALOW ; 
 scalar_t__ RTI802_SELECT ; 
 unsigned int comedi_offset_munge (struct comedi_subdevice*,unsigned int) ; 
 scalar_t__ dac_2comp ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int rti802_ao_insn_write(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct rti802_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	int i;

	outb(chan, dev->iobase + RTI802_SELECT);

	for (i = 0; i < insn->n; i++) {
		unsigned int val = data[i];

		s->readback[chan] = val;

		/* munge offset binary to two's complement if needed */
		if (devpriv->dac_coding[chan] == dac_2comp)
			val = comedi_offset_munge(s, val);

		outb(val & 0xff, dev->iobase + RTI802_DATALOW);
		outb((val >> 8) & 0xff, dev->iobase + RTI802_DATAHIGH);
	}

	return insn->n;
}