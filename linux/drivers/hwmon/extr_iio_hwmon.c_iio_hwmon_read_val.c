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
struct sensor_device_attribute {size_t index; } ;
struct iio_hwmon_state {struct iio_channel* channels; } ;
struct iio_channel {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;

/* Variables and functions */
 int IIO_POWER ; 
 struct iio_hwmon_state* dev_get_drvdata (struct device*) ; 
 int iio_get_channel_type (struct iio_channel*,int*) ; 
 int iio_read_channel_processed (struct iio_channel*,int*) ; 
 int sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t iio_hwmon_read_val(struct device *dev,
				  struct device_attribute *attr,
				  char *buf)
{
	int result;
	int ret;
	struct sensor_device_attribute *sattr = to_sensor_dev_attr(attr);
	struct iio_hwmon_state *state = dev_get_drvdata(dev);
	struct iio_channel *chan = &state->channels[sattr->index];
	enum iio_chan_type type;

	ret = iio_read_channel_processed(chan, &result);
	if (ret < 0)
		return ret;

	ret = iio_get_channel_type(chan, &type);
	if (ret < 0)
		return ret;

	if (type == IIO_POWER)
		result *= 1000; /* mili-Watts to micro-Watts conversion */

	return sprintf(buf, "%d\n", result);
}