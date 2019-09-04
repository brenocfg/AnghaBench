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
struct adxl34x {int disabled; int /*<<< orphan*/  mutex; scalar_t__ opened; int /*<<< orphan*/  suspended; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  __adxl34x_disable (struct adxl34x*) ; 
 int /*<<< orphan*/  __adxl34x_enable (struct adxl34x*) ; 
 struct adxl34x* dev_get_drvdata (struct device*) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t adxl34x_disable_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct adxl34x *ac = dev_get_drvdata(dev);
	unsigned int val;
	int error;

	error = kstrtouint(buf, 10, &val);
	if (error)
		return error;

	mutex_lock(&ac->mutex);

	if (!ac->suspended && ac->opened) {
		if (val) {
			if (!ac->disabled)
				__adxl34x_disable(ac);
		} else {
			if (ac->disabled)
				__adxl34x_enable(ac);
		}
	}

	ac->disabled = !!val;

	mutex_unlock(&ac->mutex);

	return count;
}