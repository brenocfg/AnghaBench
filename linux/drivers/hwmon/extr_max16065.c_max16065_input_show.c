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
struct max16065_data {int* adc; int /*<<< orphan*/ * range; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ADC_TO_MV (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct max16065_data* max16065_update_device (struct device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t max16065_input_show(struct device *dev,
				   struct device_attribute *da, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct max16065_data *data = max16065_update_device(dev);
	int adc = data->adc[attr->index];

	if (unlikely(adc < 0))
		return adc;

	return snprintf(buf, PAGE_SIZE, "%d\n",
			ADC_TO_MV(adc, data->range[attr->index]));
}