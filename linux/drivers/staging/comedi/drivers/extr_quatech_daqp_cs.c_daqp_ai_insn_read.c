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
struct daqp_private {scalar_t__ stop; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct daqp_private* private; } ;

/* Variables and functions */
 scalar_t__ DAQP_AUX_REG ; 
 int DAQP_CMD_ARM ; 
 int DAQP_CMD_FIFO_DATA ; 
 scalar_t__ DAQP_CMD_REG ; 
 int DAQP_CMD_RSTF ; 
 int DAQP_CMD_RSTQ ; 
 int DAQP_CMD_STOP ; 
 int DAQP_CTRL_PACER_CLK_100KHZ ; 
 scalar_t__ DAQP_CTRL_REG ; 
 scalar_t__ DAQP_STATUS_REG ; 
 int EIO ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  daqp_ai_eos ; 
 unsigned int daqp_ai_get_sample (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  daqp_ai_set_one_scanlist_entry (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int daqp_clear_events (struct comedi_device*,int) ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int daqp_ai_insn_read(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn,
			     unsigned int *data)
{
	struct daqp_private *devpriv = dev->private;
	int ret = 0;
	int i;

	if (devpriv->stop)
		return -EIO;

	outb(0, dev->iobase + DAQP_AUX_REG);

	/* Reset scan list queue */
	outb(DAQP_CMD_RSTQ, dev->iobase + DAQP_CMD_REG);

	/* Program one scan list entry */
	daqp_ai_set_one_scanlist_entry(dev, insn->chanspec, 1);

	/* Reset data FIFO (see page 28 of DAQP User's Manual) */
	outb(DAQP_CMD_RSTF, dev->iobase + DAQP_CMD_REG);

	/* Set trigger - one-shot, internal, no interrupts */
	outb(DAQP_CTRL_PACER_CLK_100KHZ, dev->iobase + DAQP_CTRL_REG);

	ret = daqp_clear_events(dev, 10000);
	if (ret)
		return ret;

	for (i = 0; i < insn->n; i++) {
		/* Start conversion */
		outb(DAQP_CMD_ARM | DAQP_CMD_FIFO_DATA,
		     dev->iobase + DAQP_CMD_REG);

		ret = comedi_timeout(dev, s, insn, daqp_ai_eos, 0);
		if (ret)
			break;

		/* clear the status event flags */
		inb(dev->iobase + DAQP_STATUS_REG);

		data[i] = daqp_ai_get_sample(dev, s);
	}

	/* stop any conversions and clear the status event flags */
	outb(DAQP_CMD_STOP, dev->iobase + DAQP_CMD_REG);
	inb(dev->iobase + DAQP_STATUS_REG);

	return ret ? ret : insn->n;
}