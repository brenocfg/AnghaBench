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
struct gpiod_data {int /*<<< orphan*/  mutex; struct gpio_desc* desc; } ;
struct gpio_desc {int /*<<< orphan*/  flags; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EPERM ; 
 int /*<<< orphan*/  FLAG_IS_OUT ; 
 struct gpiod_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (struct gpio_desc*,long) ; 
 scalar_t__ isdigit (char const) ; 
 size_t kstrtol (char const*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t value_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct gpiod_data *data = dev_get_drvdata(dev);
	struct gpio_desc *desc = data->desc;
	ssize_t status = 0;

	mutex_lock(&data->mutex);

	if (!test_bit(FLAG_IS_OUT, &desc->flags)) {
		status = -EPERM;
	} else {
		long		value;

		if (size <= 2 && isdigit(buf[0]) &&
		    (size == 1 || buf[1] == '\n'))
			value = buf[0] - '0';
		else
			status = kstrtol(buf, 0, &value);
		if (status == 0) {
			gpiod_set_value_cansleep(desc, value);
			status = size;
		}
	}

	mutex_unlock(&data->mutex);

	return status;
}