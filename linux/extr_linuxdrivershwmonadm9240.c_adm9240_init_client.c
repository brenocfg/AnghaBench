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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct adm9240_data {int vrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM9240_REG_CONFIG ; 
 int /*<<< orphan*/  ADM9240_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  ADM9240_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  ADM9240_REG_IN_MIN (int) ; 
 int /*<<< orphan*/  ADM9240_REG_TEMP_CONF ; 
 int /*<<< orphan*/  ADM9240_REG_TEMP_MAX (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 struct adm9240_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int vid_which_vrm () ; 

__attribute__((used)) static void adm9240_init_client(struct i2c_client *client)
{
	struct adm9240_data *data = i2c_get_clientdata(client);
	u8 conf = i2c_smbus_read_byte_data(client, ADM9240_REG_CONFIG);
	u8 mode = i2c_smbus_read_byte_data(client, ADM9240_REG_TEMP_CONF) & 3;

	data->vrm = vid_which_vrm(); /* need this to report vid as mV */

	dev_info(&client->dev, "Using VRM: %d.%d\n", data->vrm / 10,
			data->vrm % 10);

	if (conf & 1) { /* measurement cycle running: report state */

		dev_info(&client->dev, "status: config 0x%02x mode %u\n",
				conf, mode);

	} else { /* cold start: open limits before starting chip */
		int i;

		for (i = 0; i < 6; i++) {
			i2c_smbus_write_byte_data(client,
					ADM9240_REG_IN_MIN(i), 0);
			i2c_smbus_write_byte_data(client,
					ADM9240_REG_IN_MAX(i), 255);
		}
		i2c_smbus_write_byte_data(client,
				ADM9240_REG_FAN_MIN(0), 255);
		i2c_smbus_write_byte_data(client,
				ADM9240_REG_FAN_MIN(1), 255);
		i2c_smbus_write_byte_data(client,
				ADM9240_REG_TEMP_MAX(0), 127);
		i2c_smbus_write_byte_data(client,
				ADM9240_REG_TEMP_MAX(1), 127);

		/* start measurement cycle */
		i2c_smbus_write_byte_data(client, ADM9240_REG_CONFIG, 1);

		dev_info(&client->dev,
			 "cold start: config was 0x%02x mode %u\n", conf, mode);
	}
}