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
struct comedi_subdevice {unsigned int* readback; unsigned int maxdata; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAC02_AO_LSB (unsigned int) ; 
 scalar_t__ DAC02_AO_MSB (unsigned int) ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int dac02_ao_insn_write(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	unsigned int val;
	int i;

	for (i = 0; i < insn->n; i++) {
		val = data[i];

		s->readback[chan] = val;

		/*
		 * Unipolar outputs are true binary encoding.
		 * Bipolar outputs are complementary offset binary
		 * (that is, 0 = +full scale, maxdata = -full scale).
		 */
		if (comedi_range_is_bipolar(s, range))
			val = s->maxdata - val;

		/*
		 * DACs are double-buffered.
		 * Write LSB then MSB to latch output.
		 */
		outb((val << 4) & 0xf0, dev->iobase + DAC02_AO_LSB(chan));
		outb((val >> 4) & 0xff, dev->iobase + DAC02_AO_MSB(chan));
	}

	return insn->n;
}