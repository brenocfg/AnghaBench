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
struct comedi_subdevice {int io_bits; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct atao_private* private; } ;
struct atao_private {int /*<<< orphan*/  cfg3; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATAO_CFG3_DOUTEN1 ; 
 int /*<<< orphan*/  ATAO_CFG3_DOUTEN2 ; 
 scalar_t__ ATAO_CFG3_REG ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int comedi_dio_insn_config (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int atao_dio_insn_config(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct atao_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int mask;
	int ret;

	if (chan < 4)
		mask = 0x0f;
	else
		mask = 0xf0;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (ret)
		return ret;

	if (s->io_bits & 0x0f)
		devpriv->cfg3 |= ATAO_CFG3_DOUTEN1;
	else
		devpriv->cfg3 &= ~ATAO_CFG3_DOUTEN1;
	if (s->io_bits & 0xf0)
		devpriv->cfg3 |= ATAO_CFG3_DOUTEN2;
	else
		devpriv->cfg3 &= ~ATAO_CFG3_DOUTEN2;

	outw(devpriv->cfg3, dev->iobase + ATAO_CFG3_REG);

	return insn->n;
}