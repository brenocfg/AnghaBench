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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_SENSORS_CONFIG_REG_READ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_recv (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ms_sensors_read_config_reg(struct i2c_client *client,
				      u8 *config_reg)
{
	int ret;

	ret = i2c_smbus_write_byte(client, MS_SENSORS_CONFIG_REG_READ);
	if (ret) {
		dev_err(&client->dev, "Unable to read config register");
		return ret;
	}

	ret = i2c_master_recv(client, config_reg, 1);
	if (ret < 0) {
		dev_err(&client->dev, "Unable to read config register");
		return ret;
	}
	dev_dbg(&client->dev, "Config register :%x\n", *config_reg);

	return 0;
}