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

/* Variables and functions */
 int /*<<< orphan*/  CCS811_MEAS_MODE ; 
 int /*<<< orphan*/  CCS811_MODE_IAQ_1SEC ; 
 int ccs811_start_sensor_application (struct i2c_client*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccs811_setup(struct i2c_client *client)
{
	int ret;

	ret = ccs811_start_sensor_application(client);
	if (ret < 0)
		return ret;

	return i2c_smbus_write_byte_data(client, CCS811_MEAS_MODE,
					 CCS811_MODE_IAQ_1SEC);
}