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
struct comedi_subdevice {int maxdata; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PCMAD_CONVERT ; 
 scalar_t__ PCMAD_LSB ; 
 scalar_t__ PCMAD_MSB ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  pcmad_ai_eoc ; 

__attribute__((used)) static int pcmad_ai_insn_read(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	unsigned int val;
	int ret;
	int i;

	for (i = 0; i < insn->n; i++) {
		outb(chan, dev->iobase + PCMAD_CONVERT);

		ret = comedi_timeout(dev, s, insn, pcmad_ai_eoc, 0);
		if (ret)
			return ret;

		val = inb(dev->iobase + PCMAD_LSB) |
		      (inb(dev->iobase + PCMAD_MSB) << 8);

		/* data is shifted on the pcmad12, fix it */
		if (s->maxdata == 0x0fff)
			val >>= 4;

		if (comedi_range_is_bipolar(s, range)) {
			/* munge the two's complement value */
			val ^= ((s->maxdata + 1) >> 1);
		}

		data[i] = val;
	}

	return insn->n;
}