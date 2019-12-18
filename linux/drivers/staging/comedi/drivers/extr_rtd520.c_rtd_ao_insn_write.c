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
struct rtd_private {scalar_t__ las1; } ;
struct comedi_subdevice {int maxdata; unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; struct rtd_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ LAS0_DAC_CTRL (unsigned int) ; 
 scalar_t__ LAS0_UPDATE_DAC (unsigned int) ; 
 scalar_t__ LAS1_DAC_FIFO (unsigned int) ; 
 unsigned int comedi_offset_munge (struct comedi_subdevice*,unsigned int) ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtd_ao_eoc ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int rtd_ao_insn_write(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn,
			     unsigned int *data)
{
	struct rtd_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	int ret;
	int i;

	/* Configure the output range (table index matches the range values) */
	writew(range & 7, dev->mmio + LAS0_DAC_CTRL(chan));

	for (i = 0; i < insn->n; ++i) {
		unsigned int val = data[i];

		/* bipolar uses 2's complement values with an extended sign */
		if (comedi_range_is_bipolar(s, range)) {
			val = comedi_offset_munge(s, val);
			val |= (val & ((s->maxdata + 1) >> 1)) << 1;
		}

		/* shift the 12-bit data (+ sign) to match the register */
		val <<= 3;

		writew(val, devpriv->las1 + LAS1_DAC_FIFO(chan));
		writew(0, dev->mmio + LAS0_UPDATE_DAC(chan));

		ret = comedi_timeout(dev, s, insn, rtd_ao_eoc, 0);
		if (ret)
			return ret;

		s->readback[chan] = data[i];
	}

	return insn->n;
}