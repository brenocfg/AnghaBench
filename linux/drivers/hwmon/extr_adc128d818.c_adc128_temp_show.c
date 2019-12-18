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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adc128_data {int /*<<< orphan*/ * temp; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct adc128_data*) ; 
 int /*<<< orphan*/  PTR_ERR (struct adc128_data*) ; 
 struct adc128_data* adc128_update_device (struct device*) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t adc128_temp_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct adc128_data *data = adc128_update_device(dev);
	int index = to_sensor_dev_attr(attr)->index;
	int temp;

	if (IS_ERR(data))
		return PTR_ERR(data);

	temp = sign_extend32(data->temp[index], 8);
	return sprintf(buf, "%d\n", temp * 500);/* 0.5 degrees C resolution */
}