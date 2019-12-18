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
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; } ;

/* Variables and functions */
 int ADC ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int CVEN ; 
 scalar_t__ DAS1800_CONTROL_A ; 
 scalar_t__ DAS1800_CONTROL_C ; 
 scalar_t__ DAS1800_FIFO ; 
 scalar_t__ DAS1800_SELECT ; 
 scalar_t__ DAS1800_STATUS ; 
 int FFEN ; 
 unsigned short comedi_offset_munge (struct comedi_subdevice*,unsigned short) ; 
 int comedi_range_is_unipolar (struct comedi_subdevice*,unsigned int) ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int das1800_ai_chanspec_bits (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das1800_ai_eoc ; 
 int /*<<< orphan*/  das1800_ai_set_chanlist (struct comedi_device*,int /*<<< orphan*/ *,int) ; 
 unsigned short inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int das1800_ai_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int range = CR_RANGE(insn->chanspec);
	bool is_unipolar = comedi_range_is_unipolar(s, range);
	int ret = 0;
	int n;
	unsigned short dpnt;
	unsigned long flags;

	outb(das1800_ai_chanspec_bits(s, insn->chanspec),
	     dev->iobase + DAS1800_CONTROL_C);		/* software pacer */
	outb(CVEN, dev->iobase + DAS1800_STATUS);	/* enable conversions */
	outb(0x0, dev->iobase + DAS1800_CONTROL_A);	/* reset fifo */
	outb(FFEN, dev->iobase + DAS1800_CONTROL_A);

	das1800_ai_set_chanlist(dev, &insn->chanspec, 1);

	/* protects the indirect addressing selected by DAS1800_SELECT */
	spin_lock_irqsave(&dev->spinlock, flags);

	/* select ai fifo register */
	outb(ADC, dev->iobase + DAS1800_SELECT);

	for (n = 0; n < insn->n; n++) {
		/* trigger conversion */
		outb(0, dev->iobase + DAS1800_FIFO);

		ret = comedi_timeout(dev, s, insn, das1800_ai_eoc, 0);
		if (ret)
			break;

		dpnt = inw(dev->iobase + DAS1800_FIFO);
		if (!is_unipolar)
			dpnt = comedi_offset_munge(s, dpnt);
		data[n] = dpnt;
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	return ret ? ret : insn->n;
}