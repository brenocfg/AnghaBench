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
struct comedi_driver {struct comedi_driver* next; } ;
struct comedi_device {int /*<<< orphan*/  mutex; scalar_t__ use_count; int /*<<< orphan*/  class_dev; struct comedi_driver* driver; scalar_t__ attached; } ;

/* Variables and functions */
 int COMEDI_NUM_BOARD_MINORS ; 
 struct comedi_device* comedi_dev_get_from_minor (int) ; 
 int /*<<< orphan*/  comedi_dev_put (struct comedi_device*) ; 
 int /*<<< orphan*/  comedi_device_detach (struct comedi_device*) ; 
 struct comedi_driver* comedi_drivers ; 
 int /*<<< orphan*/  comedi_drivers_list_lock ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void comedi_driver_unregister(struct comedi_driver *driver)
{
	struct comedi_driver *prev;
	int i;

	/* unlink the driver */
	mutex_lock(&comedi_drivers_list_lock);
	if (comedi_drivers == driver) {
		comedi_drivers = driver->next;
	} else {
		for (prev = comedi_drivers; prev->next; prev = prev->next) {
			if (prev->next == driver) {
				prev->next = driver->next;
				break;
			}
		}
	}
	mutex_unlock(&comedi_drivers_list_lock);

	/* check for devices using this driver */
	for (i = 0; i < COMEDI_NUM_BOARD_MINORS; i++) {
		struct comedi_device *dev = comedi_dev_get_from_minor(i);

		if (!dev)
			continue;

		mutex_lock(&dev->mutex);
		if (dev->attached && dev->driver == driver) {
			if (dev->use_count)
				dev_warn(dev->class_dev,
					 "BUG! detaching device with use_count=%d\n",
					 dev->use_count);
			comedi_device_detach(dev);
		}
		mutex_unlock(&dev->mutex);
		comedi_dev_put(dev);
	}
}