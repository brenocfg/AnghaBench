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
struct comedi_subdevice {int n_chan; unsigned int state; } ;

/* Variables and functions */

unsigned int comedi_dio_update_state(struct comedi_subdevice *s,
				     unsigned int *data)
{
	unsigned int chanmask = (s->n_chan < 32) ? ((1 << s->n_chan) - 1)
						 : 0xffffffff;
	unsigned int mask = data[0] & chanmask;
	unsigned int bits = data[1];

	if (mask) {
		s->state &= ~mask;
		s->state |= (bits & mask);
	}

	return mask;
}