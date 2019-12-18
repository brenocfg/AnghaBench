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
struct comedi_subdevice {int n_chan; unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAC (unsigned int) ; 
 scalar_t__ DAS1800_DAC ; 
 scalar_t__ DAS1800_SELECT ; 
 unsigned int comedi_offset_munge (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int das1800_ao_insn_write(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int update_chan = s->n_chan - 1;
	unsigned long flags;
	int i;

	/* protects the indirect addressing selected by DAS1800_SELECT */
	spin_lock_irqsave(&dev->spinlock, flags);

	for (i = 0; i < insn->n; i++) {
		unsigned int val = data[i];

		s->readback[chan] = val;

		val = comedi_offset_munge(s, val);

		/* load this channel (and update if it's the last channel) */
		outb(DAC(chan), dev->iobase + DAS1800_SELECT);
		outw(val, dev->iobase + DAS1800_DAC);

		/* update all channels */
		if (chan != update_chan) {
			val = comedi_offset_munge(s, s->readback[update_chan]);

			outb(DAC(update_chan), dev->iobase + DAS1800_SELECT);
			outw(val, dev->iobase + DAS1800_DAC);
		}
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	return insn->n;
}