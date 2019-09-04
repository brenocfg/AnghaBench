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
 int AMC6821_CONF1_FANIE ; 
 int AMC6821_CONF1_PWMINV ; 
 int AMC6821_CONF1_START ; 
 int AMC6821_CONF1_THERMOVIE ; 
 int AMC6821_CONF2_LTOIE ; 
 int AMC6821_CONF2_RTFIE ; 
 int AMC6821_CONF2_RTOIE ; 
 int AMC6821_CONF3_THERM_FAN_EN ; 
 int AMC6821_CONF4_MODE ; 
 int /*<<< orphan*/  AMC6821_REG_CONF1 ; 
 int /*<<< orphan*/  AMC6821_REG_CONF2 ; 
 int /*<<< orphan*/  AMC6821_REG_CONF3 ; 
 int /*<<< orphan*/  AMC6821_REG_CONF4 ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ init ; 
 scalar_t__ pwminv ; 

__attribute__((used)) static int amc6821_init_client(struct i2c_client *client)
{
	int config;
	int err = -EIO;

	if (init) {
		config = i2c_smbus_read_byte_data(client, AMC6821_REG_CONF4);

		if (config < 0) {
				dev_err(&client->dev,
			"Error reading configuration register, aborting.\n");
				return err;
		}

		config |= AMC6821_CONF4_MODE;

		if (i2c_smbus_write_byte_data(client, AMC6821_REG_CONF4,
				config)) {
			dev_err(&client->dev,
			"Configuration register write error, aborting.\n");
			return err;
		}

		config = i2c_smbus_read_byte_data(client, AMC6821_REG_CONF3);

		if (config < 0) {
			dev_err(&client->dev,
			"Error reading configuration register, aborting.\n");
			return err;
		}

		dev_info(&client->dev, "Revision %d\n", config & 0x0f);

		config &= ~AMC6821_CONF3_THERM_FAN_EN;

		if (i2c_smbus_write_byte_data(client, AMC6821_REG_CONF3,
				config)) {
			dev_err(&client->dev,
			"Configuration register write error, aborting.\n");
			return err;
		}

		config = i2c_smbus_read_byte_data(client, AMC6821_REG_CONF2);

		if (config < 0) {
			dev_err(&client->dev,
			"Error reading configuration register, aborting.\n");
			return err;
		}

		config &= ~AMC6821_CONF2_RTFIE;
		config &= ~AMC6821_CONF2_LTOIE;
		config &= ~AMC6821_CONF2_RTOIE;
		if (i2c_smbus_write_byte_data(client,
				AMC6821_REG_CONF2, config)) {
			dev_err(&client->dev,
			"Configuration register write error, aborting.\n");
			return err;
		}

		config = i2c_smbus_read_byte_data(client, AMC6821_REG_CONF1);

		if (config < 0) {
			dev_err(&client->dev,
			"Error reading configuration register, aborting.\n");
			return err;
		}

		config &= ~AMC6821_CONF1_THERMOVIE;
		config &= ~AMC6821_CONF1_FANIE;
		config |= AMC6821_CONF1_START;
		if (pwminv)
			config |= AMC6821_CONF1_PWMINV;
		else
			config &= ~AMC6821_CONF1_PWMINV;

		if (i2c_smbus_write_byte_data(
				client, AMC6821_REG_CONF1, config)) {
			dev_err(&client->dev,
			"Configuration register write error, aborting.\n");
			return err;
		}
	}
	return 0;
}