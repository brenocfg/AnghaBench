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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_INPUT ; 
 int /*<<< orphan*/  COMEDI_OUTPUT ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_DIO_INPUT 133 
#define  INSN_CONFIG_DIO_OUTPUT 132 
#define  INSN_CONFIG_DIO_QUERY 131 
#define  INSN_CONFIG_FILTER 130 
#define  INSN_CONFIG_GET_ROUTING 129 
#define  INSN_CONFIG_SET_ROUTING 128 
 unsigned int ni_660x_get_pfi_direction (struct comedi_device*,unsigned int) ; 
 unsigned int ni_660x_get_pfi_routing (struct comedi_device*,unsigned int) ; 
 int /*<<< orphan*/  ni_660x_set_pfi_direction (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_660x_set_pfi_filter (struct comedi_device*,unsigned int,unsigned int) ; 
 int ni_660x_set_pfi_routing (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int ni_660x_dio_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	int ret;

	switch (data[0]) {
	case INSN_CONFIG_DIO_OUTPUT:
		ni_660x_set_pfi_direction(dev, chan, COMEDI_OUTPUT);
		break;

	case INSN_CONFIG_DIO_INPUT:
		ni_660x_set_pfi_direction(dev, chan, COMEDI_INPUT);
		break;

	case INSN_CONFIG_DIO_QUERY:
		data[1] = ni_660x_get_pfi_direction(dev, chan);
		break;

	case INSN_CONFIG_SET_ROUTING:
		ret = ni_660x_set_pfi_routing(dev, chan, data[1]);
		if (ret)
			return ret;
		break;

	case INSN_CONFIG_GET_ROUTING:
		data[1] = ni_660x_get_pfi_routing(dev, chan);
		break;

	case INSN_CONFIG_FILTER:
		ni_660x_set_pfi_filter(dev, chan, data[1]);
		break;

	default:
		return -EINVAL;
	}

	return insn->n;
}