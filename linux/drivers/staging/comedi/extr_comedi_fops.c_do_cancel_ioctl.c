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
struct comedi_subdevice {void* busy; int /*<<< orphan*/  async; } ;
struct comedi_device {unsigned long n_subdevices; struct comedi_subdevice* subdevices; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int do_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_cancel_ioctl(struct comedi_device *dev, unsigned long arg,
			   void *file)
{
	struct comedi_subdevice *s;

	lockdep_assert_held(&dev->mutex);
	if (arg >= dev->n_subdevices)
		return -EINVAL;
	s = &dev->subdevices[arg];
	if (!s->async)
		return -EINVAL;

	if (!s->busy)
		return 0;

	if (s->busy != file)
		return -EBUSY;

	return do_cancel(dev, s);
}