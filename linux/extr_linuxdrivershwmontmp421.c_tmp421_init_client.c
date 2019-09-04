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
 int /*<<< orphan*/  TMP421_CONFIG_REG_1 ; 
 int TMP421_CONFIG_SHUTDOWN ; 
 int /*<<< orphan*/  TMP421_CONVERSION_RATE_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tmp421_init_client(struct i2c_client *client)
{
	int config, config_orig;

	/* Set the conversion rate to 2 Hz */
	i2c_smbus_write_byte_data(client, TMP421_CONVERSION_RATE_REG, 0x05);

	/* Start conversions (disable shutdown if necessary) */
	config = i2c_smbus_read_byte_data(client, TMP421_CONFIG_REG_1);
	if (config < 0) {
		dev_err(&client->dev,
			"Could not read configuration register (%d)\n", config);
		return config;
	}

	config_orig = config;
	config &= ~TMP421_CONFIG_SHUTDOWN;

	if (config != config_orig) {
		dev_info(&client->dev, "Enable monitoring chip\n");
		i2c_smbus_write_byte_data(client, TMP421_CONFIG_REG_1, config);
	}

	return 0;
}