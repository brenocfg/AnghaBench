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
struct sensor_device_attribute_2 {size_t index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7475_data {int* range; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int*) ; 
 scalar_t__ IS_ERR (struct adt7475_data*) ; 
 int /*<<< orphan*/  PTR_ERR (struct adt7475_data*) ; 
 struct adt7475_data* adt7475_update_device (struct device*) ; 
 int clamp_val (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int* pwmfreq_table ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pwmfreq_show(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	struct adt7475_data *data = adt7475_update_device(dev);
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	int idx;

	if (IS_ERR(data))
		return PTR_ERR(data);
	idx = clamp_val(data->range[sattr->index] & 0xf, 0,
			ARRAY_SIZE(pwmfreq_table) - 1);

	return sprintf(buf, "%d\n", pwmfreq_table[idx]);
}