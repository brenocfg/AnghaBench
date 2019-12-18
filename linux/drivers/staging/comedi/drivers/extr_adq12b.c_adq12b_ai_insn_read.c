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
struct comedi_device {scalar_t__ iobase; struct adq12b_private* private; } ;
struct adq12b_private {unsigned int last_ctreg; } ;

/* Variables and functions */
 scalar_t__ ADQ12B_ADHIG ; 
 scalar_t__ ADQ12B_ADLOW ; 
 scalar_t__ ADQ12B_CTREG ; 
 unsigned int ADQ12B_CTREG_CHAN (unsigned int) ; 
 unsigned int ADQ12B_CTREG_RANGE (unsigned int) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adq12b_ai_eoc ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int adq12b_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	struct adq12b_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	unsigned int val;
	int ret;
	int i;

	/* change channel and range only if it is different from the previous */
	val = ADQ12B_CTREG_RANGE(range) | ADQ12B_CTREG_CHAN(chan);
	if (val != devpriv->last_ctreg) {
		outb(val, dev->iobase + ADQ12B_CTREG);
		devpriv->last_ctreg = val;
		usleep_range(50, 100);	/* wait for the mux to settle */
	}

	val = inb(dev->iobase + ADQ12B_ADLOW);	/* trigger A/D */

	for (i = 0; i < insn->n; i++) {
		ret = comedi_timeout(dev, s, insn, adq12b_ai_eoc, 0);
		if (ret)
			return ret;

		val = inb(dev->iobase + ADQ12B_ADHIG) << 8;
		val |= inb(dev->iobase + ADQ12B_ADLOW);	/* retriggers A/D */

		data[i] = val;
	}

	return insn->n;
}