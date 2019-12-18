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
struct auo_pixcir_ts {struct i2c_client* client; } ;

/* Variables and functions */
 int AUO_PIXCIR_POWER_MASK ; 
 int /*<<< orphan*/  AUO_PIXCIR_REG_POWER_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int auo_pixcir_power_mode(struct auo_pixcir_ts *ts, int mode)
{
	struct i2c_client *client = ts->client;
	int ret;

	ret = i2c_smbus_read_byte_data(client, AUO_PIXCIR_REG_POWER_MODE);
	if (ret < 0) {
		dev_err(&client->dev, "unable to read reg %Xh, %d\n",
			AUO_PIXCIR_REG_POWER_MODE, ret);
		return ret;
	}

	ret &= ~AUO_PIXCIR_POWER_MASK;
	ret |= mode;

	ret = i2c_smbus_write_byte_data(client, AUO_PIXCIR_REG_POWER_MODE, ret);
	if (ret) {
		dev_err(&client->dev, "unable to write reg %Xh, %d\n",
			AUO_PIXCIR_REG_POWER_MODE, ret);
		return ret;
	}

	return 0;
}