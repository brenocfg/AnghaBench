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
 int /*<<< orphan*/  MULTIQ3_BP_RESET ; 
 int MULTIQ3_CTRL_EN ; 
 int MULTIQ3_CTRL_E_CHAN (unsigned int) ; 
 scalar_t__ MULTIQ3_ENC_CTRL_REG ; 
 scalar_t__ MULTIQ3_ENC_DATA_REG ; 
 int /*<<< orphan*/  MULTIQ3_TRSFRCNTR_OL ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  multiq3_set_ctrl (struct comedi_device*,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int multiq3_encoder_insn_read(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int val;
	int i;

	for (i = 0; i < insn->n; i++) {
		/* select encoder channel */
		multiq3_set_ctrl(dev, MULTIQ3_CTRL_EN |
				      MULTIQ3_CTRL_E_CHAN(chan));

		/* reset the byte pointer */
		outb(MULTIQ3_BP_RESET, dev->iobase + MULTIQ3_ENC_CTRL_REG);

		/* latch the data */
		outb(MULTIQ3_TRSFRCNTR_OL, dev->iobase + MULTIQ3_ENC_CTRL_REG);

		/* read the 24-bit encoder data (lsb/mid/msb) */
		val = inb(dev->iobase + MULTIQ3_ENC_DATA_REG);
		val |= (inb(dev->iobase + MULTIQ3_ENC_DATA_REG) << 8);
		val |= (inb(dev->iobase + MULTIQ3_ENC_DATA_REG) << 16);

		/*
		 * Munge the data so that the reset value is in the middle
		 * of the maxdata range, i.e.:
		 *
		 * real value	comedi value
		 * 0xffffff	0x7fffff	1 negative count
		 * 0x000000	0x800000	reset value
		 * 0x000001	0x800001	1 positive count
		 *
		 * It's possible for the 24-bit counter to overflow but it
		 * would normally take _quite_ a few turns. A 2000 line
		 * encoder in quadrature results in 8000 counts/rev. So about
		 * 1048 turns in either direction can be measured without
		 * an overflow.
		 */
		data[i] = (val + ((s->maxdata + 1) >> 1)) & s->maxdata;
	}

	return insn->n;
}