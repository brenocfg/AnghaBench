#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_dev_attr {int address; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int channel; int scale; } ;

/* Variables and functions */
 int HX711_GAIN_MAX ; 
 TYPE_1__* hx711_gain_to_scale ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t hx711_scale_available_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	struct iio_dev_attr *iio_attr = to_iio_dev_attr(attr);
	int channel = iio_attr->address;
	int i, len = 0;

	for (i = 0; i < HX711_GAIN_MAX; i++)
		if (hx711_gain_to_scale[i].channel == channel)
			len += sprintf(buf + len, "0.%09d ",
					hx711_gain_to_scale[i].scale);

	len += sprintf(buf + len, "\n");

	return len;
}