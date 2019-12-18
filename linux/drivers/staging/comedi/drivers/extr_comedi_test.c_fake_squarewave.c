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
typedef  unsigned int u64 ;
struct waveform_private {unsigned int wf_amplitude; int wf_period; } ;
struct comedi_subdevice {int maxdata; TYPE_1__* range_table; } ;
struct comedi_krange {scalar_t__ min; scalar_t__ max; } ;
struct comedi_device {struct comedi_subdevice* read_subdev; struct waveform_private* private; } ;
struct TYPE_2__ {struct comedi_krange* range; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned int,scalar_t__) ; 

__attribute__((used)) static unsigned short fake_squarewave(struct comedi_device *dev,
				      unsigned int range_index,
				      unsigned int current_time)
{
	struct waveform_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	unsigned int offset = s->maxdata / 2;
	u64 value;
	const struct comedi_krange *krange =
	    &s->range_table->range[range_index];

	value = s->maxdata;
	value *= devpriv->wf_amplitude;
	do_div(value, krange->max - krange->min);

	/* get one of two values for square-wave and clamp */
	if (current_time < devpriv->wf_period / 2) {
		if (offset < value)
			value = 0;		/* negative saturation */
		else
			value = offset - value;
	} else {
		value += offset;
		if (value > s->maxdata)
			value = s->maxdata;	/* positive saturation */
	}

	return value;
}