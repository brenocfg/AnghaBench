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
struct gpio_desc {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  char ssize_t ;

/* Variables and functions */
 struct gpiod_data* dev_get_drvdata (struct device*) ; 
 char gpiod_get_value_cansleep (struct gpio_desc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t value_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct gpiod_data *data = dev_get_drvdata(dev);
	struct gpio_desc *desc = data->desc;
	ssize_t			status;

	mutex_lock(&data->mutex);

	status = gpiod_get_value_cansleep(desc);
	if (status < 0)
		goto err;

	buf[0] = '0' + status;
	buf[1] = '\n';
	status = 2;
err:
	mutex_unlock(&data->mutex);

	return status;
}