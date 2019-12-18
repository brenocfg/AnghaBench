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
struct sensor_device_attribute {int /*<<< orphan*/  index; } ;
struct lm73_data {int /*<<< orphan*/  client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ s32 ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct lm73_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ i2c_smbus_read_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_show(struct device *dev, struct device_attribute *da,
			 char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct lm73_data *data = dev_get_drvdata(dev);
	int temp;

	s32 err = i2c_smbus_read_word_swapped(data->client, attr->index);
	if (err < 0)
		return err;

	/* use integer division instead of equivalent right shift to
	   guarantee arithmetic shift and preserve the sign */
	temp = (((s16) err) * 250) / 32;
	return scnprintf(buf, PAGE_SIZE, "%d\n", temp);
}