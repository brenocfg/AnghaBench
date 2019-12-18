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
struct max6639_platform_data {int ppr; scalar_t__ pwm_polarity; int /*<<< orphan*/  rpm_range; } ;
struct max6639_data {int ppr; int rpm_range; int* temp_therm; int* temp_alert; int* temp_ot; int* pwm; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX6639_FAN_CONFIG1_PWM ; 
 int MAX6639_FAN_CONFIG3_THERM_FULL_SPEED ; 
 int MAX6639_GCONFIG_CH2_LOCAL ; 
 int MAX6639_GCONFIG_DISABLE_TIMEOUT ; 
 int MAX6639_GCONFIG_POR ; 
 int MAX6639_GCONFIG_PWM_FREQ_HI ; 
 int /*<<< orphan*/  MAX6639_REG_ALERT_LIMIT (int) ; 
 int /*<<< orphan*/  MAX6639_REG_FAN_CONFIG1 (int) ; 
 int /*<<< orphan*/  MAX6639_REG_FAN_CONFIG2a (int) ; 
 int /*<<< orphan*/  MAX6639_REG_FAN_CONFIG3 (int) ; 
 int /*<<< orphan*/  MAX6639_REG_FAN_PPR (int) ; 
 int /*<<< orphan*/  MAX6639_REG_GCONFIG ; 
 int /*<<< orphan*/  MAX6639_REG_OT_LIMIT (int) ; 
 int /*<<< orphan*/  MAX6639_REG_TARGTDUTY (int) ; 
 int /*<<< orphan*/  MAX6639_REG_THERM_LIMIT (int) ; 
 struct max6639_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int rpm_range_to_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max6639_init_client(struct i2c_client *client,
			       struct max6639_data *data)
{
	struct max6639_platform_data *max6639_info =
		dev_get_platdata(&client->dev);
	int i;
	int rpm_range = 1; /* default: 4000 RPM */
	int err;

	/* Reset chip to default values, see below for GCONFIG setup */
	err = i2c_smbus_write_byte_data(client, MAX6639_REG_GCONFIG,
				  MAX6639_GCONFIG_POR);
	if (err)
		goto exit;

	/* Fans pulse per revolution is 2 by default */
	if (max6639_info && max6639_info->ppr > 0 &&
			max6639_info->ppr < 5)
		data->ppr = max6639_info->ppr;
	else
		data->ppr = 2;
	data->ppr -= 1;

	if (max6639_info)
		rpm_range = rpm_range_to_reg(max6639_info->rpm_range);
	data->rpm_range = rpm_range;

	for (i = 0; i < 2; i++) {

		/* Set Fan pulse per revolution */
		err = i2c_smbus_write_byte_data(client,
				MAX6639_REG_FAN_PPR(i),
				data->ppr << 6);
		if (err)
			goto exit;

		/* Fans config PWM, RPM */
		err = i2c_smbus_write_byte_data(client,
			MAX6639_REG_FAN_CONFIG1(i),
			MAX6639_FAN_CONFIG1_PWM | rpm_range);
		if (err)
			goto exit;

		/* Fans PWM polarity high by default */
		if (max6639_info && max6639_info->pwm_polarity == 0)
			err = i2c_smbus_write_byte_data(client,
				MAX6639_REG_FAN_CONFIG2a(i), 0x00);
		else
			err = i2c_smbus_write_byte_data(client,
				MAX6639_REG_FAN_CONFIG2a(i), 0x02);
		if (err)
			goto exit;

		/*
		 * /THERM full speed enable,
		 * PWM frequency 25kHz, see also GCONFIG below
		 */
		err = i2c_smbus_write_byte_data(client,
			MAX6639_REG_FAN_CONFIG3(i),
			MAX6639_FAN_CONFIG3_THERM_FULL_SPEED | 0x03);
		if (err)
			goto exit;

		/* Max. temp. 80C/90C/100C */
		data->temp_therm[i] = 80;
		data->temp_alert[i] = 90;
		data->temp_ot[i] = 100;
		err = i2c_smbus_write_byte_data(client,
				MAX6639_REG_THERM_LIMIT(i),
				data->temp_therm[i]);
		if (err)
			goto exit;
		err = i2c_smbus_write_byte_data(client,
				MAX6639_REG_ALERT_LIMIT(i),
				data->temp_alert[i]);
		if (err)
			goto exit;
		err = i2c_smbus_write_byte_data(client,
				MAX6639_REG_OT_LIMIT(i), data->temp_ot[i]);
		if (err)
			goto exit;

		/* PWM 120/120 (i.e. 100%) */
		data->pwm[i] = 120;
		err = i2c_smbus_write_byte_data(client,
				MAX6639_REG_TARGTDUTY(i), data->pwm[i]);
		if (err)
			goto exit;
	}
	/* Start monitoring */
	err = i2c_smbus_write_byte_data(client, MAX6639_REG_GCONFIG,
		MAX6639_GCONFIG_DISABLE_TIMEOUT | MAX6639_GCONFIG_CH2_LOCAL |
		MAX6639_GCONFIG_PWM_FREQ_HI);
exit:
	return err;
}