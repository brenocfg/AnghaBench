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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ams_input_disable () ; 
 int ams_input_enable () ; 
 int /*<<< orphan*/  ams_input_mutex ; 
 unsigned long joystick ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t ams_input_store_joystick(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long enable;
	int error = 0;
	int ret;

	ret = kstrtoul(buf, 0, &enable);
	if (ret)
		return ret;
	if (enable > 1)
		return -EINVAL;

	mutex_lock(&ams_input_mutex);

	if (enable != joystick) {
		if (enable)
			error = ams_input_enable();
		else
			ams_input_disable();
	}

	mutex_unlock(&ams_input_mutex);

	return error ? error : count;
}