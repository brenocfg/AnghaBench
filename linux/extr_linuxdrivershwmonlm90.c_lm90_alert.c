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
typedef  int u16 ;
struct lm90_data {int flags; int alert_alarms; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  enum i2c_alert_protocol { ____Placeholder_i2c_alert_protocol } i2c_alert_protocol ;

/* Variables and functions */
 int I2C_PROTOCOL_SMBUS_ALERT ; 
 int LM90_HAVE_BROKEN_ALERT ; 
 int /*<<< orphan*/  LM90_REG_R_CONFIG1 ; 
 int /*<<< orphan*/  LM90_REG_W_CONFIG1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct lm90_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lm90_is_tripped (struct i2c_client*,int*) ; 
 int lm90_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lm90_alert(struct i2c_client *client, enum i2c_alert_protocol type,
		       unsigned int flag)
{
	u16 alarms;

	if (type != I2C_PROTOCOL_SMBUS_ALERT)
		return;

	if (lm90_is_tripped(client, &alarms)) {
		/*
		 * Disable ALERT# output, because these chips don't implement
		 * SMBus alert correctly; they should only hold the alert line
		 * low briefly.
		 */
		struct lm90_data *data = i2c_get_clientdata(client);

		if ((data->flags & LM90_HAVE_BROKEN_ALERT) &&
		    (alarms & data->alert_alarms)) {
			int config;

			dev_dbg(&client->dev, "Disabling ALERT#\n");
			config = lm90_read_reg(client, LM90_REG_R_CONFIG1);
			if (config >= 0)
				i2c_smbus_write_byte_data(client,
							  LM90_REG_W_CONFIG1,
							  config | 0x80);
		}
	} else {
		dev_info(&client->dev, "Everything OK\n");
	}
}