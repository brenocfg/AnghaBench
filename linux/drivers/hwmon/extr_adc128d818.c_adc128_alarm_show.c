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
typedef  int u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adc128_data {int alarms; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct adc128_data*) ; 
 int /*<<< orphan*/  PTR_ERR (struct adc128_data*) ; 
 struct adc128_data* adc128_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t adc128_alarm_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct adc128_data *data = adc128_update_device(dev);
	int mask = 1 << to_sensor_dev_attr(attr)->index;
	u8 alarms;

	if (IS_ERR(data))
		return PTR_ERR(data);

	/*
	 * Clear an alarm after reporting it to user space. If it is still
	 * active, the next update sequence will set the alarm bit again.
	 */
	alarms = data->alarms;
	data->alarms &= ~mask;

	return sprintf(buf, "%u\n", !!(alarms & mask));
}