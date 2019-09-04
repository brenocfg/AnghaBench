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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct adt7411_data {int vref_cached; scalar_t__ next_update; struct i2c_client* client; } ;

/* Variables and functions */
 int ADT7411_CFG3_REF_VDD ; 
 int /*<<< orphan*/  ADT7411_REG_CFG3 ; 
 scalar_t__ HZ ; 
 int adt7411_read_in_vdd (struct device*,int /*<<< orphan*/ ,int*) ; 
 struct adt7411_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hwmon_in_input ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int adt7411_update_vref(struct device *dev)
{
	struct adt7411_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int val;

	if (time_after_eq(jiffies, data->next_update)) {
		val = i2c_smbus_read_byte_data(client, ADT7411_REG_CFG3);
		if (val < 0)
			return val;

		if (val & ADT7411_CFG3_REF_VDD) {
			val = adt7411_read_in_vdd(dev, hwmon_in_input,
						  &data->vref_cached);
			if (val < 0)
				return val;
		} else {
			data->vref_cached = 2250;
		}

		data->next_update = jiffies + HZ;
	}

	return 0;
}