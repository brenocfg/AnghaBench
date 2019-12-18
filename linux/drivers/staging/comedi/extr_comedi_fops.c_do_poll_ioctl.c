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
struct comedi_subdevice {void* busy; int (* poll ) (struct comedi_device*,struct comedi_subdevice*) ;} ;
struct comedi_device {unsigned long n_subdevices; struct comedi_subdevice* subdevices; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int stub1 (struct comedi_device*,struct comedi_subdevice*) ; 

__attribute__((used)) static int do_poll_ioctl(struct comedi_device *dev, unsigned long arg,
			 void *file)
{
	struct comedi_subdevice *s;

	lockdep_assert_held(&dev->mutex);
	if (arg >= dev->n_subdevices)
		return -EINVAL;
	s = &dev->subdevices[arg];

	if (!s->busy)
		return 0;

	if (s->busy != file)
		return -EBUSY;

	if (s->poll)
		return s->poll(dev, s);

	return -EINVAL;
}