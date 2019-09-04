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
struct adm1026_data {int* gpio_config; int config2; int config3; } ;

/* Variables and functions */
 scalar_t__ ADM1026_REG_CONFIG2 ; 
 scalar_t__ ADM1026_REG_CONFIG3 ; 
 scalar_t__ ADM1026_REG_GPIO_CFG_0_3 ; 
 int /*<<< orphan*/  adm1026_print_gpio (struct i2c_client*) ; 
 int /*<<< orphan*/  adm1026_write_value (struct i2c_client*,scalar_t__,int) ; 
 int* gpio_fan ; 
 int* gpio_input ; 
 int* gpio_inverted ; 
 int* gpio_normal ; 
 int* gpio_output ; 
 struct adm1026_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static void adm1026_fixup_gpio(struct i2c_client *client)
{
	struct adm1026_data *data = i2c_get_clientdata(client);
	int i;
	int value;

	/* Make the changes requested. */
	/*
	 * We may need to unlock/stop monitoring or soft-reset the
	 *    chip before we can make changes.  This hasn't been
	 *    tested much.  FIXME
	 */

	/* Make outputs */
	for (i = 0; i <= 16; ++i) {
		if (gpio_output[i] >= 0 && gpio_output[i] <= 16)
			data->gpio_config[gpio_output[i]] |= 0x01;
		/* if GPIO0-7 is output, it isn't a FAN tach */
		if (gpio_output[i] >= 0 && gpio_output[i] <= 7)
			data->config2 |= 1 << gpio_output[i];
	}

	/* Input overrides output */
	for (i = 0; i <= 16; ++i) {
		if (gpio_input[i] >= 0 && gpio_input[i] <= 16)
			data->gpio_config[gpio_input[i]] &= ~0x01;
		/* if GPIO0-7 is input, it isn't a FAN tach */
		if (gpio_input[i] >= 0 && gpio_input[i] <= 7)
			data->config2 |= 1 << gpio_input[i];
	}

	/* Inverted */
	for (i = 0; i <= 16; ++i) {
		if (gpio_inverted[i] >= 0 && gpio_inverted[i] <= 16)
			data->gpio_config[gpio_inverted[i]] &= ~0x02;
	}

	/* Normal overrides inverted */
	for (i = 0; i <= 16; ++i) {
		if (gpio_normal[i] >= 0 && gpio_normal[i] <= 16)
			data->gpio_config[gpio_normal[i]] |= 0x02;
	}

	/* Fan overrides input and output */
	for (i = 0; i <= 7; ++i) {
		if (gpio_fan[i] >= 0 && gpio_fan[i] <= 7)
			data->config2 &= ~(1 << gpio_fan[i]);
	}

	/* Write new configs to registers */
	adm1026_write_value(client, ADM1026_REG_CONFIG2, data->config2);
	data->config3 = (data->config3 & 0x3f)
			| ((data->gpio_config[16] & 0x03) << 6);
	adm1026_write_value(client, ADM1026_REG_CONFIG3, data->config3);
	for (i = 15, value = 0; i >= 0; --i) {
		value <<= 2;
		value |= data->gpio_config[i] & 0x03;
		if ((i & 0x03) == 0) {
			adm1026_write_value(client,
					ADM1026_REG_GPIO_CFG_0_3 + i/4,
					value);
			value = 0;
		}
	}

	/* Print the new config */
	adm1026_print_gpio(client);
}