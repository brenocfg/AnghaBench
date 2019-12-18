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
struct comedi_driver {char const* driver_name; int (* attach ) (struct comedi_device*,struct comedi_devconfig*) ;int /*<<< orphan*/  module; struct comedi_driver* next; scalar_t__ num_names; } ;
struct comedi_device {char const* board_name; struct comedi_driver* driver; scalar_t__ board_ptr; int /*<<< orphan*/  class_dev; scalar_t__ attached; int /*<<< orphan*/  mutex; } ;
struct comedi_devconfig {int /*<<< orphan*/  board_name; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  comedi_device_detach (struct comedi_device*) ; 
 int comedi_device_postconfig (struct comedi_device*) ; 
 struct comedi_driver* comedi_drivers ; 
 int /*<<< orphan*/  comedi_drivers_list_lock ; 
 scalar_t__ comedi_recognize (struct comedi_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_report_boards (struct comedi_driver*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int stub1 (struct comedi_device*,struct comedi_devconfig*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int comedi_device_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct comedi_driver *driv;
	int ret;

	lockdep_assert_held(&dev->mutex);
	if (dev->attached)
		return -EBUSY;

	mutex_lock(&comedi_drivers_list_lock);
	for (driv = comedi_drivers; driv; driv = driv->next) {
		if (!try_module_get(driv->module))
			continue;
		if (driv->num_names) {
			dev->board_ptr = comedi_recognize(driv, it->board_name);
			if (dev->board_ptr)
				break;
		} else if (strcmp(driv->driver_name, it->board_name) == 0) {
			break;
		}
		module_put(driv->module);
	}
	if (!driv) {
		/*  recognize has failed if we get here */
		/*  report valid board names before returning error */
		for (driv = comedi_drivers; driv; driv = driv->next) {
			if (!try_module_get(driv->module))
				continue;
			comedi_report_boards(driv);
			module_put(driv->module);
		}
		ret = -EIO;
		goto out;
	}
	if (!driv->attach) {
		/* driver does not support manual configuration */
		dev_warn(dev->class_dev,
			 "driver '%s' does not support attach using comedi_config\n",
			 driv->driver_name);
		module_put(driv->module);
		ret = -EIO;
		goto out;
	}
	dev->driver = driv;
	dev->board_name = dev->board_ptr ? *(const char **)dev->board_ptr
					 : dev->driver->driver_name;
	ret = driv->attach(dev, it);
	if (ret >= 0)
		ret = comedi_device_postconfig(dev);
	if (ret < 0) {
		comedi_device_detach(dev);
		module_put(driv->module);
	}
	/* On success, the driver module count has been incremented. */
out:
	mutex_unlock(&comedi_drivers_list_lock);
	return ret;
}