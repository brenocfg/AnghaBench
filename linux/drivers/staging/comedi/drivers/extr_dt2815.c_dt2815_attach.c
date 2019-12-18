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
struct dt2815_private {struct comedi_lrange const** range_type_list; } ;
struct comedi_subdevice {int maxdata; int n_chan; struct comedi_lrange const** range_table_list; int /*<<< orphan*/  insn_read; int /*<<< orphan*/  insn_write; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  type; } ;
struct comedi_lrange {int dummy; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  class_dev; struct comedi_subdevice* subdevices; } ;
struct comedi_devconfig {int* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 scalar_t__ DT2815_DATA ; 
 scalar_t__ DT2815_STATUS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SDF_WRITABLE ; 
 struct dt2815_private* comedi_alloc_devpriv (struct comedi_device*,int) ; 
 int comedi_alloc_subdevices (struct comedi_device*,int) ; 
 int comedi_request_region (struct comedi_device*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dt2815_ao_insn ; 
 int /*<<< orphan*/  dt2815_ao_insn_read ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 struct comedi_lrange range_0_32mA ; 
 struct comedi_lrange range_4_20mA ; 
 struct comedi_lrange range_bipolar5 ; 
 struct comedi_lrange range_unipolar5 ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dt2815_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct dt2815_private *devpriv;
	struct comedi_subdevice *s;
	int i;
	const struct comedi_lrange *current_range_type, *voltage_range_type;
	int ret;

	ret = comedi_request_region(dev, it->options[0], 0x2);
	if (ret)
		return ret;

	ret = comedi_alloc_subdevices(dev, 1);
	if (ret)
		return ret;

	devpriv = comedi_alloc_devpriv(dev, sizeof(*devpriv));
	if (!devpriv)
		return -ENOMEM;

	s = &dev->subdevices[0];
	/* ao subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->maxdata = 0xfff;
	s->n_chan = 8;
	s->insn_write = dt2815_ao_insn;
	s->insn_read = dt2815_ao_insn_read;
	s->range_table_list = devpriv->range_type_list;

	current_range_type = (it->options[3])
	    ? &range_4_20mA : &range_0_32mA;
	voltage_range_type = (it->options[2])
	    ? &range_bipolar5 : &range_unipolar5;
	for (i = 0; i < 8; i++) {
		devpriv->range_type_list[i] = (it->options[5 + i])
		    ? current_range_type : voltage_range_type;
	}

	/* Init the 2815 */
	outb(0x00, dev->iobase + DT2815_STATUS);
	for (i = 0; i < 100; i++) {
		/* This is incredibly slow (approx 20 ms) */
		unsigned int status;

		usleep_range(1000, 3000);
		status = inb(dev->iobase + DT2815_STATUS);
		if (status == 4) {
			unsigned int program;

			program = (it->options[4] & 0x3) << 3 | 0x7;
			outb(program, dev->iobase + DT2815_DATA);
			dev_dbg(dev->class_dev, "program: 0x%x (@t=%d)\n",
				program, i);
			break;
		} else if (status != 0x00) {
			dev_dbg(dev->class_dev,
				"unexpected status 0x%x (@t=%d)\n",
				status, i);
			if (status & 0x60)
				outb(0x00, dev->iobase + DT2815_STATUS);
		}
	}

	return 0;
}