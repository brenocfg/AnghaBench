#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct regulator {int dummy; } ;
struct lm87_data {int channel; int config; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int CHAN_NO_FAN (int) ; 
 int CHAN_TEMP3 ; 
 int CHAN_VCC_5V ; 
 int /*<<< orphan*/  IS_ERR (struct regulator*) ; 
 int /*<<< orphan*/  LM87_REG_AIN_MAX (int) ; 
 int /*<<< orphan*/  LM87_REG_AIN_MIN (int) ; 
 int /*<<< orphan*/  LM87_REG_CHANNEL_MODE ; 
 int /*<<< orphan*/  LM87_REG_CONFIG ; 
 int /*<<< orphan*/  LM87_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  LM87_REG_IN_MIN (int) ; 
 int /*<<< orphan*/ * LM87_REG_TEMP_HIGH ; 
 int /*<<< orphan*/ * LM87_REG_TEMP_LOW ; 
 scalar_t__ dev_get_platdata (TYPE_1__*) ; 
 int devm_add_action (TYPE_1__*,int /*<<< orphan*/ ,struct i2c_client*) ; 
 struct regulator* devm_regulator_get_optional (TYPE_1__*,char*) ; 
 struct lm87_data* i2c_get_clientdata (struct i2c_client*) ; 
 int lm87_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm87_restore_config ; 
 int /*<<< orphan*/  lm87_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int regulator_get_voltage (struct regulator*) ; 

__attribute__((used)) static int lm87_init_client(struct i2c_client *client)
{
	struct lm87_data *data = i2c_get_clientdata(client);
	int rc;
	struct device_node *of_node = client->dev.of_node;
	u8 val = 0;
	struct regulator *vcc = NULL;

	if (of_node) {
		if (of_property_read_bool(of_node, "has-temp3"))
			val |= CHAN_TEMP3;
		if (of_property_read_bool(of_node, "has-in6"))
			val |= CHAN_NO_FAN(0);
		if (of_property_read_bool(of_node, "has-in7"))
			val |= CHAN_NO_FAN(1);
		vcc = devm_regulator_get_optional(&client->dev, "vcc");
		if (!IS_ERR(vcc)) {
			if (regulator_get_voltage(vcc) == 5000000)
				val |= CHAN_VCC_5V;
		}
		data->channel = val;
		lm87_write_value(client,
				LM87_REG_CHANNEL_MODE, data->channel);
	} else if (dev_get_platdata(&client->dev)) {
		data->channel = *(u8 *)dev_get_platdata(&client->dev);
		lm87_write_value(client,
				 LM87_REG_CHANNEL_MODE, data->channel);
	} else {
		data->channel = lm87_read_value(client, LM87_REG_CHANNEL_MODE);
	}
	data->config = lm87_read_value(client, LM87_REG_CONFIG) & 0x6F;

	rc = devm_add_action(&client->dev, lm87_restore_config, client);
	if (rc)
		return rc;

	if (!(data->config & 0x01)) {
		int i;

		/* Limits are left uninitialized after power-up */
		for (i = 1; i < 6; i++) {
			lm87_write_value(client, LM87_REG_IN_MIN(i), 0x00);
			lm87_write_value(client, LM87_REG_IN_MAX(i), 0xFF);
		}
		for (i = 0; i < 2; i++) {
			lm87_write_value(client, LM87_REG_TEMP_HIGH[i], 0x7F);
			lm87_write_value(client, LM87_REG_TEMP_LOW[i], 0x00);
			lm87_write_value(client, LM87_REG_AIN_MIN(i), 0x00);
			lm87_write_value(client, LM87_REG_AIN_MAX(i), 0xFF);
		}
		if (data->channel & CHAN_TEMP3) {
			lm87_write_value(client, LM87_REG_TEMP_HIGH[2], 0x7F);
			lm87_write_value(client, LM87_REG_TEMP_LOW[2], 0x00);
		} else {
			lm87_write_value(client, LM87_REG_IN_MIN(0), 0x00);
			lm87_write_value(client, LM87_REG_IN_MAX(0), 0xFF);
		}
	}

	/* Make sure Start is set and INT#_Clear is clear */
	if ((data->config & 0x09) != 0x01)
		lm87_write_value(client, LM87_REG_CONFIG,
				 (data->config & 0x77) | 0x01);
	return 0;
}