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
struct ni_private {TYPE_1__* counter_dev; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct comedi_subdevice* subdevices; struct ni_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * counters; } ;

/* Variables and functions */
 size_t NI_GPCT_SUBDEV (unsigned short) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_tio_handle_interrupt (int /*<<< orphan*/ *,struct comedi_subdevice*) ; 

__attribute__((used)) static void handle_gpct_interrupt(struct comedi_device *dev,
				  unsigned short counter_index)
{
#ifdef PCIDMA
	struct ni_private *devpriv = dev->private;
	struct comedi_subdevice *s;

	s = &dev->subdevices[NI_GPCT_SUBDEV(counter_index)];

	ni_tio_handle_interrupt(&devpriv->counter_dev->counters[counter_index],
				s);
	comedi_handle_events(dev, s);
#endif
}