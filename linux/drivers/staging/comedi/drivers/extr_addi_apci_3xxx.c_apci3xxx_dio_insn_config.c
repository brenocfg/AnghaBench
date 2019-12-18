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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned int INSN_CONFIG_DIO_QUERY ; 
 int comedi_dio_insn_config (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static int apci3xxx_dio_insn_config(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int mask = 0;
	int ret;

	/*
	 * Port 0 (channels 0-7) are always inputs
	 * Port 1 (channels 8-15) are always outputs
	 * Port 2 (channels 16-23) are programmable i/o
	 */
	if (data[0] != INSN_CONFIG_DIO_QUERY) {
		/* ignore all other instructions for ports 0 and 1 */
		if (chan < 16)
			return -EINVAL;

		/* changing any channel in port 2 changes the entire port */
		mask = 0xff0000;
	}

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (ret)
		return ret;

	/* update port 2 configuration */
	outl((s->io_bits >> 24) & 0xff, dev->iobase + 224);

	return insn->n;
}