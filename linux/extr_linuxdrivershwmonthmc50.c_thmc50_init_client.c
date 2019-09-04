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
struct thmc50_data {int analog_out; scalar_t__ type; int has_temp3; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THMC50_REG_ANALOG_OUT ; 
 int /*<<< orphan*/  THMC50_REG_CONF ; 
 scalar_t__ adm1022 ; 
 void* i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void thmc50_init_client(struct thmc50_data *data)
{
	struct i2c_client *client = data->client;
	int config;

	data->analog_out = i2c_smbus_read_byte_data(client,
						    THMC50_REG_ANALOG_OUT);
	/* set up to at least 1 */
	if (data->analog_out == 0) {
		data->analog_out = 1;
		i2c_smbus_write_byte_data(client, THMC50_REG_ANALOG_OUT,
					  data->analog_out);
	}
	config = i2c_smbus_read_byte_data(client, THMC50_REG_CONF);
	config |= 0x1;	/* start the chip if it is in standby mode */
	if (data->type == adm1022 && (config & (1 << 7)))
		data->has_temp3 = 1;
	i2c_smbus_write_byte_data(client, THMC50_REG_CONF, config);
}