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
struct ni_gpct_device {unsigned int** regs; } ;
struct ni_gpct {unsigned int counter_index; unsigned int chip_index; struct ni_gpct_device* counter_dev; } ;
struct comedi_subdevice {struct ni_gpct* private; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 size_t NITIO_LOADA_REG (unsigned int) ; 
 size_t NITIO_LOADB_REG (unsigned int) ; 
 unsigned int ni_tio_read_sw_save_reg (struct comedi_device*,struct comedi_subdevice*) ; 

int ni_tio_insn_read(struct comedi_device *dev,
		     struct comedi_subdevice *s,
		     struct comedi_insn *insn,
		     unsigned int *data)
{
	struct ni_gpct *counter = s->private;
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int channel = CR_CHAN(insn->chanspec);
	unsigned int cidx = counter->counter_index;
	unsigned int chip = counter->chip_index;
	int i;

	for (i = 0; i < insn->n; i++) {
		switch (channel) {
		case 0:
			data[i] = ni_tio_read_sw_save_reg(dev, s);
			break;
		case 1:
			data[i] =
			    counter_dev->regs[chip][NITIO_LOADA_REG(cidx)];
			break;
		case 2:
			data[i] =
			    counter_dev->regs[chip][NITIO_LOADB_REG(cidx)];
			break;
		}
	}
	return insn->n;
}