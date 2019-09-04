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
struct ad7418_data {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7418_REG_CONF ; 
 int /*<<< orphan*/  AD7418_REG_CONF2 ; 
 scalar_t__ ad7417 ; 
 scalar_t__ ad7418 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct ad7418_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ad7418_init_client(struct i2c_client *client)
{
	struct ad7418_data *data = i2c_get_clientdata(client);

	int reg = i2c_smbus_read_byte_data(client, AD7418_REG_CONF);
	if (reg < 0) {
		dev_err(&client->dev, "cannot read configuration register\n");
	} else {
		dev_info(&client->dev, "configuring for mode 1\n");
		i2c_smbus_write_byte_data(client, AD7418_REG_CONF, reg & 0xfe);

		if (data->type == ad7417 || data->type == ad7418)
			i2c_smbus_write_byte_data(client,
						AD7418_REG_CONF2, 0x00);
	}
}