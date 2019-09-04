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
typedef  scalar_t__ u8 ;
struct lm63_data {int config; int config_fan; int kind; int pwm1_freq; int lut_size; int trutherm; int lut_temp_highres; int pwm_highres; int remote_unsigned; int /*<<< orphan*/  max_convrate_hz; int /*<<< orphan*/  update_interval; struct i2c_client* client; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 scalar_t__ LM63_MAX_CONVRATE ; 
 int /*<<< orphan*/  LM63_MAX_CONVRATE_HZ ; 
 int /*<<< orphan*/  LM63_REG_CONFIG1 ; 
 int /*<<< orphan*/  LM63_REG_CONFIG_FAN ; 
 int /*<<< orphan*/  LM63_REG_CONVRATE ; 
 int /*<<< orphan*/  LM63_REG_PWM_FREQ ; 
 int /*<<< orphan*/  LM96163_MAX_CONVRATE_HZ ; 
 int /*<<< orphan*/  LM96163_REG_CONFIG_ENHANCED ; 
 int /*<<< orphan*/  LM96163_REG_TRUTHERM ; 
 int /*<<< orphan*/  UPDATE_INTERVAL (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
#define  lm63 130 
#define  lm64 129 
#define  lm96163 128 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void lm63_init_client(struct lm63_data *data)
{
	struct i2c_client *client = data->client;
	struct device *dev = &client->dev;
	u8 convrate;

	data->config = i2c_smbus_read_byte_data(client, LM63_REG_CONFIG1);
	data->config_fan = i2c_smbus_read_byte_data(client,
						    LM63_REG_CONFIG_FAN);

	/* Start converting if needed */
	if (data->config & 0x40) { /* standby */
		dev_dbg(dev, "Switching to operational mode\n");
		data->config &= 0xA7;
		i2c_smbus_write_byte_data(client, LM63_REG_CONFIG1,
					  data->config);
	}
	/* Tachometer is always enabled on LM64 */
	if (data->kind == lm64)
		data->config |= 0x04;

	/* We may need pwm1_freq before ever updating the client data */
	data->pwm1_freq = i2c_smbus_read_byte_data(client, LM63_REG_PWM_FREQ);
	if (data->pwm1_freq == 0)
		data->pwm1_freq = 1;

	switch (data->kind) {
	case lm63:
	case lm64:
		data->max_convrate_hz = LM63_MAX_CONVRATE_HZ;
		data->lut_size = 8;
		break;
	case lm96163:
		data->max_convrate_hz = LM96163_MAX_CONVRATE_HZ;
		data->lut_size = 12;
		data->trutherm
		  = i2c_smbus_read_byte_data(client,
					     LM96163_REG_TRUTHERM) & 0x02;
		break;
	}
	convrate = i2c_smbus_read_byte_data(client, LM63_REG_CONVRATE);
	if (unlikely(convrate > LM63_MAX_CONVRATE))
		convrate = LM63_MAX_CONVRATE;
	data->update_interval = UPDATE_INTERVAL(data->max_convrate_hz,
						convrate);

	/*
	 * For LM96163, check if high resolution PWM
	 * and unsigned temperature format is enabled.
	 */
	if (data->kind == lm96163) {
		u8 config_enhanced
		  = i2c_smbus_read_byte_data(client,
					     LM96163_REG_CONFIG_ENHANCED);
		if (config_enhanced & 0x20)
			data->lut_temp_highres = true;
		if ((config_enhanced & 0x10)
		    && !(data->config_fan & 0x08) && data->pwm1_freq == 8)
			data->pwm_highres = true;
		if (config_enhanced & 0x08)
			data->remote_unsigned = true;
	}

	/* Show some debug info about the LM63 configuration */
	if (data->kind == lm63)
		dev_dbg(dev, "Alert/tach pin configured for %s\n",
			(data->config & 0x04) ? "tachometer input" :
			"alert output");
	dev_dbg(dev, "PWM clock %s kHz, output frequency %u Hz\n",
		(data->config_fan & 0x08) ? "1.4" : "360",
		((data->config_fan & 0x08) ? 700 : 180000) / data->pwm1_freq);
	dev_dbg(dev, "PWM output active %s, %s mode\n",
		(data->config_fan & 0x10) ? "low" : "high",
		(data->config_fan & 0x20) ? "manual" : "auto");
}