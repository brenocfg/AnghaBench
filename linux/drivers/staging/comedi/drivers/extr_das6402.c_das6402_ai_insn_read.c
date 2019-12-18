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
struct comedi_subdevice {int n_chan; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int AREF_DIFF ; 
 unsigned int CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int DAS6402_AI_MUX_HI (unsigned int) ; 
 int DAS6402_AI_MUX_LO (unsigned int) ; 
 scalar_t__ DAS6402_AI_MUX_REG ; 
 scalar_t__ DAS6402_CTRL_REG ; 
 int /*<<< orphan*/  DAS6402_CTRL_SOFT_TRIG ; 
 int /*<<< orphan*/  DAS6402_MODE_POLLED ; 
 int EINVAL ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das6402_ai_clear_eoc (struct comedi_device*) ; 
 int /*<<< orphan*/  das6402_ai_eoc ; 
 unsigned int das6402_ai_read_sample (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  das6402_ai_set_mode (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das6402_ai_soft_trig (struct comedi_device*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int das6402_ai_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int aref = CR_AREF(insn->chanspec);
	int ret;
	int i;

	if (aref == AREF_DIFF && chan > (s->n_chan / 2))
		return -EINVAL;

	/* enable software conversion trigger */
	outb(DAS6402_CTRL_SOFT_TRIG, dev->iobase + DAS6402_CTRL_REG);

	das6402_ai_set_mode(dev, s, insn->chanspec, DAS6402_MODE_POLLED);

	/* load the mux for single channel conversion */
	outw(DAS6402_AI_MUX_HI(chan) | DAS6402_AI_MUX_LO(chan),
	     dev->iobase + DAS6402_AI_MUX_REG);

	for (i = 0; i < insn->n; i++) {
		das6402_ai_clear_eoc(dev);
		das6402_ai_soft_trig(dev);

		ret = comedi_timeout(dev, s, insn, das6402_ai_eoc, 0);
		if (ret)
			break;

		data[i] = das6402_ai_read_sample(dev, s);
	}

	das6402_ai_clear_eoc(dev);

	return insn->n;
}