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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_IS_OUT ; 
 struct gpiod_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gpiod_get_direction (struct gpio_desc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t direction_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct gpiod_data *data = dev_get_drvdata(dev);
	struct gpio_desc *desc = data->desc;
	ssize_t			status;

	mutex_lock(&data->mutex);

	gpiod_get_direction(desc);
	status = sprintf(buf, "%s\n",
			test_bit(FLAG_IS_OUT, &desc->flags)
				? "out" : "in");

	mutex_unlock(&data->mutex);

	return status;
}