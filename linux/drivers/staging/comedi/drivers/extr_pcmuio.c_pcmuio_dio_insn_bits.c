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
struct comedi_subdevice {int n_chan; unsigned int state; unsigned int io_bits; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 unsigned int pcmuio_read (struct comedi_device*,int,int /*<<< orphan*/ ,int) ; 
 int pcmuio_subdevice_to_asic (struct comedi_subdevice*) ; 
 int pcmuio_subdevice_to_port (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcmuio_write (struct comedi_device*,unsigned int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcmuio_dio_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	int asic = pcmuio_subdevice_to_asic(s);
	int port = pcmuio_subdevice_to_port(s);
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
		pcmuio_write(dev, val, asic, 0, port);
	}

	/* get inverted state of the channels from the port */
	val = pcmuio_read(dev, asic, 0, port);

	/* return the true state of the channels */
	data[1] = ~val & chanmask;

	return insn->n;
}