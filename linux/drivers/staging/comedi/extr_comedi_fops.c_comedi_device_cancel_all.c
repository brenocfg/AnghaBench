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
struct comedi_subdevice {scalar_t__ async; } ;
struct comedi_device {int n_subdevices; struct comedi_subdevice* subdevices; int /*<<< orphan*/  attached; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void comedi_device_cancel_all(struct comedi_device *dev)
{
	struct comedi_subdevice *s;
	int i;

	lockdep_assert_held(&dev->mutex);
	if (!dev->attached)
		return;

	for (i = 0; i < dev->n_subdevices; i++) {
		s = &dev->subdevices[i];
		if (s->async)
			do_cancel(dev, s);
	}
}