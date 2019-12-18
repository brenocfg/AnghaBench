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
struct pmbus_data {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_attributes ; 
 int pmbus_add_fan_attributes (struct i2c_client*,struct pmbus_data*) ; 
 int pmbus_add_samples_attributes (struct i2c_client*,struct pmbus_data*) ; 
 int pmbus_add_sensor_attrs (struct i2c_client*,struct pmbus_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_attributes ; 
 int /*<<< orphan*/  temp_attributes ; 
 int /*<<< orphan*/  voltage_attributes ; 

__attribute__((used)) static int pmbus_find_attributes(struct i2c_client *client,
				 struct pmbus_data *data)
{
	int ret;

	/* Voltage sensors */
	ret = pmbus_add_sensor_attrs(client, data, "in", voltage_attributes,
				     ARRAY_SIZE(voltage_attributes));
	if (ret)
		return ret;

	/* Current sensors */
	ret = pmbus_add_sensor_attrs(client, data, "curr", current_attributes,
				     ARRAY_SIZE(current_attributes));
	if (ret)
		return ret;

	/* Power sensors */
	ret = pmbus_add_sensor_attrs(client, data, "power", power_attributes,
				     ARRAY_SIZE(power_attributes));
	if (ret)
		return ret;

	/* Temperature sensors */
	ret = pmbus_add_sensor_attrs(client, data, "temp", temp_attributes,
				     ARRAY_SIZE(temp_attributes));
	if (ret)
		return ret;

	/* Fans */
	ret = pmbus_add_fan_attributes(client, data);
	if (ret)
		return ret;

	ret = pmbus_add_samples_attributes(client, data);
	return ret;
}