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
struct das16cs_private {unsigned short misc1; } ;
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct das16cs_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned short DAS16CS_MISC1_DAC0CS ; 
 unsigned short DAS16CS_MISC1_DAC1CS ; 
 unsigned short DAS16CS_MISC1_DACCLK ; 
 unsigned short DAS16CS_MISC1_DACSD ; 
 unsigned short DAS16CS_MISC1_DAC_MASK ; 
 scalar_t__ DAS16CS_MISC1_REG ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int das16cs_ao_insn_write(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	struct das16cs_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int val = s->readback[chan];
	unsigned short misc1;
	int bit;
	int i;

	for (i = 0; i < insn->n; i++) {
		val = data[i];

		outw(devpriv->misc1, dev->iobase + DAS16CS_MISC1_REG);
		udelay(1);

		/* raise the DACxCS line for the non-selected channel */
		misc1 = devpriv->misc1 & ~DAS16CS_MISC1_DAC_MASK;
		if (chan)
			misc1 |= DAS16CS_MISC1_DAC0CS;
		else
			misc1 |= DAS16CS_MISC1_DAC1CS;

		outw(misc1, dev->iobase + DAS16CS_MISC1_REG);
		udelay(1);

		for (bit = 15; bit >= 0; bit--) {
			if ((val >> bit) & 0x1)
				misc1 |= DAS16CS_MISC1_DACSD;
			else
				misc1 &= ~DAS16CS_MISC1_DACSD;
			outw(misc1, dev->iobase + DAS16CS_MISC1_REG);
			udelay(1);
			outw(misc1 | DAS16CS_MISC1_DACCLK,
			     dev->iobase + DAS16CS_MISC1_REG);
			udelay(1);
		}
		/*
		 * Make both DAC0CS and DAC1CS high to load
		 * the new data and update analog the output
		 */
		outw(misc1 | DAS16CS_MISC1_DAC0CS | DAS16CS_MISC1_DAC1CS,
		     dev->iobase + DAS16CS_MISC1_REG);
	}
	s->readback[chan] = val;

	return insn->n;
}