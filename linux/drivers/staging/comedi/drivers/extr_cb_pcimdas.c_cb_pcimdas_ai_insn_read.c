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
struct comedi_device {struct cb_pcimdas_private* private; } ;
struct cb_pcimdas_private {scalar_t__ daqio; scalar_t__ BADR3; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PCIMDAS_AI_REG ; 
 scalar_t__ PCIMDAS_AI_SOFTTRIG_REG ; 
 unsigned int PCIMDAS_BURST_CONV_EN ; 
 scalar_t__ PCIMDAS_BURST_REG ; 
 scalar_t__ PCIMDAS_GAIN_REG ; 
 unsigned int PCIMDAS_MUX (unsigned int,unsigned int) ; 
 scalar_t__ PCIMDAS_MUX_REG ; 
 scalar_t__ PCIMDAS_PACER_REG ; 
 unsigned int PCIMDAS_PACER_SRC_MASK ; 
 unsigned int PCIMDAS_PACER_SRC_POLLED ; 
 int /*<<< orphan*/  cb_pcimdas_ai_eoc ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int inb (scalar_t__) ; 
 unsigned int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int cb_pcimdas_ai_insn_read(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	struct cb_pcimdas_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	int n;
	unsigned int d;
	int ret;

	/*  only support sw initiated reads from a single channel */

	/* configure for sw initiated read */
	d = inb(devpriv->BADR3 + PCIMDAS_PACER_REG);
	if ((d & PCIMDAS_PACER_SRC_MASK) != PCIMDAS_PACER_SRC_POLLED) {
		d &= ~PCIMDAS_PACER_SRC_MASK;
		d |= PCIMDAS_PACER_SRC_POLLED;
		outb(d, devpriv->BADR3 + PCIMDAS_PACER_REG);
	}

	/* set bursting off, conversions on */
	outb(PCIMDAS_BURST_CONV_EN, devpriv->BADR3 + PCIMDAS_BURST_REG);

	/* set range */
	outb(range, devpriv->BADR3 + PCIMDAS_GAIN_REG);

	/* set mux for single channel scan */
	outb(PCIMDAS_MUX(chan, chan), devpriv->BADR3 + PCIMDAS_MUX_REG);

	/* convert n samples */
	for (n = 0; n < insn->n; n++) {
		/* trigger conversion */
		outw(0, devpriv->daqio + PCIMDAS_AI_SOFTTRIG_REG);

		/* wait for conversion to end */
		ret = comedi_timeout(dev, s, insn, cb_pcimdas_ai_eoc, 0);
		if (ret)
			return ret;

		/* read data */
		data[n] = inw(devpriv->daqio + PCIMDAS_AI_REG);
	}

	/* return the number of samples read/written */
	return n;
}