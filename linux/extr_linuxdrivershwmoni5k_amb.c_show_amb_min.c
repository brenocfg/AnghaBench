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
struct i5k_amb_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int amb_read_byte (struct i5k_amb_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amb_reg_temp_min (int /*<<< orphan*/ ) ; 
 struct i5k_amb_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_amb_min(struct device *dev,
			     struct device_attribute *devattr,
			     char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct i5k_amb_data *data = dev_get_drvdata(dev);
	return sprintf(buf, "%d\n",
		500 * amb_read_byte(data, amb_reg_temp_min(attr->index)));
}