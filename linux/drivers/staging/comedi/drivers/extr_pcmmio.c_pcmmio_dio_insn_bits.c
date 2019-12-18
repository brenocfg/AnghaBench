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
struct comedi_subdevice {int index; int n_chan; unsigned int state; unsigned int io_bits; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 unsigned int pcmmio_dio_read (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcmmio_dio_write (struct comedi_device*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcmmio_dio_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	/* subdevice 2 uses ports 0-2, subdevice 3 uses ports 3-5 */
	int port = s->index == 2 ? 0 : 3;
	unsigned int chanmask = (1 << s->n_chan) - 1;
	unsigned int mask;
	unsigned int val;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		/*
		 * Outputs are inverted, invert the state and
		 * update the channels.
		 *
		 * The s->io_bits mask makes sure the input channels
		 * are '0' so that the outputs pins stay in a high
		 * z-state.
		 */
		val = ~s->state & chanmask;
		val &= s->io_bits;
		pcmmio_dio_write(dev, val, 0, port);
	}

	/* get inverted state of the channels from the port */
	val = pcmmio_dio_read(dev, 0, port);

	/* return the true state of the channels */
	data[1] = ~val & chanmask;

	return insn->n;
}