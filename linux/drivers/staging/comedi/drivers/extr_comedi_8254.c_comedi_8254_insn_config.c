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
struct comedi_subdevice {struct comedi_8254* private; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct comedi_8254 {int (* insn_config ) (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ;scalar_t__* busy; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 unsigned int I8254_BINARY ; 
 unsigned int I8254_MODE0 ; 
#define  INSN_CONFIG_8254_READ_STATUS 130 
#define  INSN_CONFIG_RESET 129 
#define  INSN_CONFIG_SET_COUNTER_MODE 128 
 int comedi_8254_set_mode (struct comedi_8254*,unsigned int,unsigned int) ; 
 unsigned int comedi_8254_status (struct comedi_8254*,unsigned int) ; 
 int stub1 (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*) ; 

__attribute__((used)) static int comedi_8254_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	struct comedi_8254 *i8254 = s->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	int ret;

	if (i8254->busy[chan])
		return -EBUSY;

	switch (data[0]) {
	case INSN_CONFIG_RESET:
		ret = comedi_8254_set_mode(i8254, chan,
					   I8254_MODE0 | I8254_BINARY);
		if (ret)
			return ret;
		break;
	case INSN_CONFIG_SET_COUNTER_MODE:
		ret = comedi_8254_set_mode(i8254, chan, data[1]);
		if (ret)
			return ret;
		break;
	case INSN_CONFIG_8254_READ_STATUS:
		data[1] = comedi_8254_status(i8254, chan);
		break;
	default:
		/*
		 * If available, call the driver provided (*insn_config)
		 * to handle any driver implemented instructions.
		 */
		if (i8254->insn_config)
			return i8254->insn_config(dev, s, insn, data);

		return -EINVAL;
	}

	return insn->n;
}