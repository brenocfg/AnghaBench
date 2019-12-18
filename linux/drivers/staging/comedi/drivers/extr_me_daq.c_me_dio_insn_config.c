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
struct me_private_data {int /*<<< orphan*/  ctrl2; } ;
struct comedi_subdevice {int io_bits; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; struct me_private_data* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_CTRL2_PORT_A_ENA ; 
 int /*<<< orphan*/  ME_CTRL2_PORT_B_ENA ; 
 scalar_t__ ME_CTRL2_REG ; 
 int comedi_dio_insn_config (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int me_dio_insn_config(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn,
			      unsigned int *data)
{
	struct me_private_data *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int mask;
	int ret;

	if (chan < 16)
		mask = 0x0000ffff;
	else
		mask = 0xffff0000;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (ret)
		return ret;

	if (s->io_bits & 0x0000ffff)
		devpriv->ctrl2 |= ME_CTRL2_PORT_A_ENA;
	else
		devpriv->ctrl2 &= ~ME_CTRL2_PORT_A_ENA;
	if (s->io_bits & 0xffff0000)
		devpriv->ctrl2 |= ME_CTRL2_PORT_B_ENA;
	else
		devpriv->ctrl2 &= ~ME_CTRL2_PORT_B_ENA;

	writew(devpriv->ctrl2, dev->mmio + ME_CTRL2_REG);

	return insn->n;
}