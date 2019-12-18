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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ANALOG_POWER_OFF ; 
 int ANALOG_POWER_ON ; 
 int CPU_POWER_OFF ; 
 int /*<<< orphan*/  SYSTEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rohm_ts_power_off(struct i2c_client *client)
{
	int error;

	error = i2c_smbus_write_byte_data(client, SYSTEM,
					  ANALOG_POWER_ON | CPU_POWER_OFF);
	if (error) {
		dev_err(&client->dev,
			"failed to power off device CPU: %d\n", error);
		return error;
	}

	error = i2c_smbus_write_byte_data(client, SYSTEM,
					  ANALOG_POWER_OFF | CPU_POWER_OFF);
	if (error)
		dev_err(&client->dev,
			"failed to power off the device: %d\n", error);

	return error;
}