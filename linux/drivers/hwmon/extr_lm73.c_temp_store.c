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
typedef  int ssize_t ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  LM73_TEMP_MAX ; 
 int /*<<< orphan*/  LM73_TEMP_MIN ; 
 int clamp_val (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lm73_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,short) ; 
 int kstrtol (char const*,int,long*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_store(struct device *dev, struct device_attribute *da,
			  const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct lm73_data *data = dev_get_drvdata(dev);
	long temp;
	short value;
	s32 err;

	int status = kstrtol(buf, 10, &temp);
	if (status < 0)
		return status;

	/* Write value */
	value = clamp_val(temp / 250, LM73_TEMP_MIN, LM73_TEMP_MAX) << 5;
	err = i2c_smbus_write_word_swapped(data->client, attr->index, value);
	return (err < 0) ? err : count;
}