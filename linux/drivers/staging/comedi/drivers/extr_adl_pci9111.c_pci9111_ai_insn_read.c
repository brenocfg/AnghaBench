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
struct comedi_subdevice {unsigned int maxdata; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI9111_AI_CHANNEL_REG ; 
 scalar_t__ PCI9111_AI_FIFO_REG ; 
 unsigned int PCI9111_AI_RANGE (unsigned int) ; 
 unsigned int PCI9111_AI_RANGE_MASK ; 
 scalar_t__ PCI9111_AI_RANGE_STAT_REG ; 
 scalar_t__ PCI9111_SOFT_TRIG_REG ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int inb (scalar_t__) ; 
 unsigned int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  pci9111_ai_eoc ; 
 int /*<<< orphan*/  pci9111_fifo_reset (struct comedi_device*) ; 

__attribute__((used)) static int pci9111_ai_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	unsigned int maxdata = s->maxdata;
	unsigned int invert = (maxdata + 1) >> 1;
	unsigned int shift = (maxdata == 0xffff) ? 0 : 4;
	unsigned int status;
	int ret;
	int i;

	outb(chan, dev->iobase + PCI9111_AI_CHANNEL_REG);

	status = inb(dev->iobase + PCI9111_AI_RANGE_STAT_REG);
	if ((status & PCI9111_AI_RANGE_MASK) != range) {
		outb(PCI9111_AI_RANGE(range),
		     dev->iobase + PCI9111_AI_RANGE_STAT_REG);
	}

	pci9111_fifo_reset(dev);

	for (i = 0; i < insn->n; i++) {
		/* Generate a software trigger */
		outb(0, dev->iobase + PCI9111_SOFT_TRIG_REG);

		ret = comedi_timeout(dev, s, insn, pci9111_ai_eoc, 0);
		if (ret) {
			pci9111_fifo_reset(dev);
			return ret;
		}

		data[i] = inw(dev->iobase + PCI9111_AI_FIFO_REG);
		data[i] = ((data[i] >> shift) & maxdata) ^ invert;
	}

	return i;
}