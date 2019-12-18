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
struct lm85_data {int /*<<< orphan*/ * pwm_freq; int /*<<< orphan*/  freq_map_size; int /*<<< orphan*/  freq_map; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int FREQ_FROM_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ADT7468_HFPWM (struct lm85_data*) ; 
 struct lm85_data* lm85_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pwm_freq_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct lm85_data *data = lm85_update_device(dev);
	int freq;

	if (IS_ADT7468_HFPWM(data))
		freq = 22500;
	else
		freq = FREQ_FROM_REG(data->freq_map, data->freq_map_size,
				     data->pwm_freq[nr]);

	return sprintf(buf, "%d\n", freq);
}