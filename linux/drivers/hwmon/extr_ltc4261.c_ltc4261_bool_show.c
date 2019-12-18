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
typedef  int u8 ;
struct sensor_device_attribute {int index; } ;
struct ltc4261_data {int* regs; int /*<<< orphan*/  client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ltc4261_data*) ; 
 size_t LTC4261_FAULT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PTR_ERR (struct ltc4261_data*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,size_t,int) ; 
 struct ltc4261_data* ltc4261_update_device (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ltc4261_bool_show(struct device *dev,
				 struct device_attribute *da, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct ltc4261_data *data = ltc4261_update_device(dev);
	u8 fault;

	if (IS_ERR(data))
		return PTR_ERR(data);

	fault = data->regs[LTC4261_FAULT] & attr->index;
	if (fault)		/* Clear reported faults in chip register */
		i2c_smbus_write_byte_data(data->client, LTC4261_FAULT, ~fault);

	return snprintf(buf, PAGE_SIZE, "%d\n", fault ? 1 : 0);
}