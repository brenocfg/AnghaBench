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
struct adc128_data {int mode; scalar_t__ regulator; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC128_REG_CONFIG ; 
 int /*<<< orphan*/  ADC128_REG_CONFIG_ADV ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adc128_init_client(struct adc128_data *data)
{
	struct i2c_client *client = data->client;
	int err;

	/*
	 * Reset chip to defaults.
	 * This makes most other initializations unnecessary.
	 */
	err = i2c_smbus_write_byte_data(client, ADC128_REG_CONFIG, 0x80);
	if (err)
		return err;

	/* Set operation mode, if non-default */
	if (data->mode != 0) {
		err = i2c_smbus_write_byte_data(client,
						ADC128_REG_CONFIG_ADV,
						data->mode << 1);
		if (err)
			return err;
	}

	/* Start monitoring */
	err = i2c_smbus_write_byte_data(client, ADC128_REG_CONFIG, 0x01);
	if (err)
		return err;

	/* If external vref is selected, configure the chip to use it */
	if (data->regulator) {
		err = i2c_smbus_write_byte_data(client,
						ADC128_REG_CONFIG_ADV, 0x01);
		if (err)
			return err;
	}

	return 0;
}