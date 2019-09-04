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
typedef  scalar_t__ u64 ;
struct raw_device_data {int /*<<< orphan*/ * binding; scalar_t__ inuse; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 scalar_t__ MAJOR (scalar_t__) ; 
 scalar_t__ MINOR (scalar_t__) ; 
 scalar_t__ MKDEV (scalar_t__,int) ; 
 scalar_t__ RAW_MAJOR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bdget (scalar_t__) ; 
 int /*<<< orphan*/  bdput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,scalar_t__) ; 
 int max_raw_minors ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_class ; 
 struct raw_device_data* raw_devices ; 
 int /*<<< orphan*/  raw_mutex ; 

__attribute__((used)) static int bind_set(int number, u64 major, u64 minor)
{
	dev_t dev = MKDEV(major, minor);
	struct raw_device_data *rawdev;
	int err = 0;

	if (number <= 0 || number >= max_raw_minors)
		return -EINVAL;

	if (MAJOR(dev) != major || MINOR(dev) != minor)
		return -EINVAL;

	rawdev = &raw_devices[number];

	/*
	 * This is like making block devices, so demand the
	 * same capability
	 */
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	/*
	 * For now, we don't need to check that the underlying
	 * block device is present or not: we can do that when
	 * the raw device is opened.  Just check that the
	 * major/minor numbers make sense.
	 */

	if (MAJOR(dev) == 0 && dev != 0)
		return -EINVAL;

	mutex_lock(&raw_mutex);
	if (rawdev->inuse) {
		mutex_unlock(&raw_mutex);
		return -EBUSY;
	}
	if (rawdev->binding) {
		bdput(rawdev->binding);
		module_put(THIS_MODULE);
	}
	if (!dev) {
		/* unbind */
		rawdev->binding = NULL;
		device_destroy(raw_class, MKDEV(RAW_MAJOR, number));
	} else {
		rawdev->binding = bdget(dev);
		if (rawdev->binding == NULL) {
			err = -ENOMEM;
		} else {
			dev_t raw = MKDEV(RAW_MAJOR, number);
			__module_get(THIS_MODULE);
			device_destroy(raw_class, raw);
			device_create(raw_class, NULL, raw, NULL,
				      "raw%d", number);
		}
	}
	mutex_unlock(&raw_mutex);
	return err;
}