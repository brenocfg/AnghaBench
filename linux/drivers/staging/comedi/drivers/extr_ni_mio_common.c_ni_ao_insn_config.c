#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ni_private {TYPE_1__* mite; } ;
struct ni_board_struct {unsigned int ao_speed; int /*<<< orphan*/  ao_fifo_depth; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {struct ni_private* private; struct ni_board_struct* board_ptr; } ;
struct TYPE_2__ {unsigned int fifo_size; } ;

/* Variables and functions */
#define  COMEDI_INPUT 132 
#define  COMEDI_OUTPUT 131 
 int EINVAL ; 
#define  INSN_CONFIG_ARM 130 
#define  INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS 129 
#define  INSN_CONFIG_GET_HARDWARE_BUFFER_SIZE 128 
 unsigned int comedi_samples_to_bytes (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int ni_ao_arm (struct comedi_device*,struct comedi_subdevice*) ; 

__attribute__((used)) static int ni_ao_insn_config(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn, unsigned int *data)
{
	const struct ni_board_struct *board = dev->board_ptr;
	struct ni_private *devpriv = dev->private;
	unsigned int nbytes;

	switch (data[0]) {
	case INSN_CONFIG_GET_HARDWARE_BUFFER_SIZE:
		switch (data[1]) {
		case COMEDI_OUTPUT:
			nbytes = comedi_samples_to_bytes(s,
							 board->ao_fifo_depth);
			data[2] = 1 + nbytes;
			if (devpriv->mite)
				data[2] += devpriv->mite->fifo_size;
			break;
		case COMEDI_INPUT:
			data[2] = 0;
			break;
		default:
			return -EINVAL;
		}
		return 0;
	case INSN_CONFIG_ARM:
		return ni_ao_arm(dev, s);
	case INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS:
		/* we don't care about actual channels */
		/* data[3] : chanlist_len */
		data[1] = board->ao_speed * data[3];
		data[2] = 0;
		return 0;
	default:
		break;
	}

	return -EINVAL;
}