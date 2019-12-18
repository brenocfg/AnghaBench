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
struct das800_private {unsigned int do_bits; } ;
struct comedi_subdevice {int maxdata; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  spinlock; struct das800_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL1 ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS800_GAIN ; 
 scalar_t__ DAS800_MSB ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das800_ai_eoc ; 
 unsigned int das800_ai_get_sample (struct comedi_device*) ; 
 int /*<<< orphan*/  das800_disable (struct comedi_device*) ; 
 int /*<<< orphan*/  das800_ind_write (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int das800_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	struct das800_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	unsigned long irq_flags;
	unsigned int val;
	int ret;
	int i;

	das800_disable(dev);

	/* set multiplexer */
	spin_lock_irqsave(&dev->spinlock, irq_flags);
	das800_ind_write(dev, chan | devpriv->do_bits, CONTROL1);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	/* set gain / range */
	if (s->maxdata == 0x0fff && range)
		range += 0x7;
	range &= 0xf;
	outb(range, dev->iobase + DAS800_GAIN);

	udelay(5);

	for (i = 0; i < insn->n; i++) {
		/* trigger conversion */
		outb_p(0, dev->iobase + DAS800_MSB);

		ret = comedi_timeout(dev, s, insn, das800_ai_eoc, 0);
		if (ret)
			return ret;

		val = das800_ai_get_sample(dev);
		if (s->maxdata == 0x0fff)
			val >>= 4;	/* 12-bit sample */
		data[i] = val & s->maxdata;
	}

	return insn->n;
}