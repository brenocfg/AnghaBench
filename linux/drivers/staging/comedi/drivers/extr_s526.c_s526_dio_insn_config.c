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
struct comedi_subdevice {int io_bits; int /*<<< orphan*/  state; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S526_DIO_CTRL_GRP1_OUT ; 
 int /*<<< orphan*/  S526_DIO_CTRL_GRP2_OUT ; 
 scalar_t__ S526_DIO_CTRL_REG ; 
 int comedi_dio_insn_config (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s526_dio_insn_config(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int mask;
	int ret;

	/*
	 * Digital I/O can be configured as inputs or outputs in
	 * groups of 4; DIO group 1 (DIO0-3) and DIO group 2 (DIO4-7).
	 */
	if (chan < 4)
		mask = 0x0f;
	else
		mask = 0xf0;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (ret)
		return ret;

	if (s->io_bits & 0x0f)
		s->state |= S526_DIO_CTRL_GRP1_OUT;
	else
		s->state &= ~S526_DIO_CTRL_GRP1_OUT;
	if (s->io_bits & 0xf0)
		s->state |= S526_DIO_CTRL_GRP2_OUT;
	else
		s->state &= ~S526_DIO_CTRL_GRP2_OUT;

	outw(s->state, dev->iobase + S526_DIO_CTRL_REG);

	return insn->n;
}