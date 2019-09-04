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
struct module {int dummy; } ;
struct iio_trigger {scalar_t__ id; int /*<<< orphan*/  dev; int /*<<< orphan*/  list; int /*<<< orphan*/  name; struct module* owner; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __iio_trigger_find_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,unsigned long) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iio_trigger_ida ; 
 int /*<<< orphan*/  iio_trigger_list ; 
 int /*<<< orphan*/  iio_trigger_list_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

int __iio_trigger_register(struct iio_trigger *trig_info,
			   struct module *this_mod)
{
	int ret;

	trig_info->owner = this_mod;

	trig_info->id = ida_simple_get(&iio_trigger_ida, 0, 0, GFP_KERNEL);
	if (trig_info->id < 0)
		return trig_info->id;

	/* Set the name used for the sysfs directory etc */
	dev_set_name(&trig_info->dev, "trigger%ld",
		     (unsigned long) trig_info->id);

	ret = device_add(&trig_info->dev);
	if (ret)
		goto error_unregister_id;

	/* Add to list of available triggers held by the IIO core */
	mutex_lock(&iio_trigger_list_lock);
	if (__iio_trigger_find_by_name(trig_info->name)) {
		pr_err("Duplicate trigger name '%s'\n", trig_info->name);
		ret = -EEXIST;
		goto error_device_del;
	}
	list_add_tail(&trig_info->list, &iio_trigger_list);
	mutex_unlock(&iio_trigger_list_lock);

	return 0;

error_device_del:
	mutex_unlock(&iio_trigger_list_lock);
	device_del(&trig_info->dev);
error_unregister_id:
	ida_simple_remove(&iio_trigger_ida, trig_info->id);
	return ret;
}