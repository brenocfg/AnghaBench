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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int COMEDI_OUTPUT ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSCDR ; 
 int /*<<< orphan*/  CSCIR ; 
 unsigned int PAMR ; 
 unsigned int PBMR ; 
 unsigned int PCMR ; 
 int comedi_dio_insn_config (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*,int /*<<< orphan*/ ) ; 
 unsigned int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dnp_dio_insn_config(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int mask;
	unsigned int val;
	int ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	if (ret)
		return ret;

	if (chan < 8) {			/* Port A */
		mask = 1 << chan;
		outb(PAMR, CSCIR);
	} else if (chan < 16) {		/* Port B */
		mask = 1 << (chan - 8);
		outb(PBMR, CSCIR);
	} else {			/* Port C */
		/*
		 * We have to pay attention with port C.
		 * This is the meaning of PCMR:
		 *   Bit in PCMR:              7 6 5 4 3 2 1 0
		 *   Corresponding port C pin: d 3 d 2 d 1 d 0   d= don't touch
		 *
		 * Multiplication by 2 brings bits into correct position
		 * for PCMR!
		 */
		mask = 1 << ((chan - 16) * 2);
		outb(PCMR, CSCIR);
	}

	val = inb(CSCDR);
	if (data[0] == COMEDI_OUTPUT)
		val |= mask;
	else
		val &= ~mask;
	outb(val, CSCDR);

	return insn->n;
}