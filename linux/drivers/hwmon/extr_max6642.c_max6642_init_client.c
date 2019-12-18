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
struct max6642_data {void** temp_high; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX6642_REG_R_CONFIG ; 
 int /*<<< orphan*/  MAX6642_REG_R_LOCAL_HIGH ; 
 int /*<<< orphan*/  MAX6642_REG_R_REMOTE_HIGH ; 
 int /*<<< orphan*/  MAX6642_REG_W_CONFIG ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void max6642_init_client(struct max6642_data *data,
				struct i2c_client *client)
{
	u8 config;

	/*
	 * Start the conversions.
	 */
	config = i2c_smbus_read_byte_data(client, MAX6642_REG_R_CONFIG);
	if (config & 0x40)
		i2c_smbus_write_byte_data(client, MAX6642_REG_W_CONFIG,
					  config & 0xBF); /* run */

	data->temp_high[0] = i2c_smbus_read_byte_data(client,
				MAX6642_REG_R_LOCAL_HIGH);
	data->temp_high[1] = i2c_smbus_read_byte_data(client,
				MAX6642_REG_R_REMOTE_HIGH);
}