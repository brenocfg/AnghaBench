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
struct dt2815_private {unsigned int* ao_readback; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct dt2815_private* private; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ DT2815_DATA ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dt2815_ao_status ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int dt2815_ao_insn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	struct dt2815_private *devpriv = dev->private;
	int i;
	int chan = CR_CHAN(insn->chanspec);
	unsigned int lo, hi;
	int ret;

	for (i = 0; i < insn->n; i++) {
		lo = ((data[i] & 0x0f) << 4) | (chan << 1) | 0x01;
		hi = (data[i] & 0xff0) >> 4;

		ret = comedi_timeout(dev, s, insn, dt2815_ao_status, 0x00);
		if (ret)
			return ret;

		outb(lo, dev->iobase + DT2815_DATA);

		ret = comedi_timeout(dev, s, insn, dt2815_ao_status, 0x10);
		if (ret)
			return ret;

		devpriv->ao_readback[chan] = data[i];
	}
	return i;
}