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
struct auo_pixcir_ts_platdata {scalar_t__ int_setting; } ;
struct auo_pixcir_ts {int touch_ind_mode; struct auo_pixcir_ts_platdata* pdata; struct i2c_client* client; } ;

/* Variables and functions */
 int AUO_PIXCIR_INT_MODE_MASK ; 
 int AUO_PIXCIR_INT_POL_HIGH ; 
 scalar_t__ AUO_PIXCIR_INT_TOUCH_IND ; 
 int /*<<< orphan*/  AUO_PIXCIR_REG_INT_SETTING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int auo_pixcir_int_config(struct auo_pixcir_ts *ts,
					   int int_setting)
{
	struct i2c_client *client = ts->client;
	const struct auo_pixcir_ts_platdata *pdata = ts->pdata;
	int ret;

	ret = i2c_smbus_read_byte_data(client, AUO_PIXCIR_REG_INT_SETTING);
	if (ret < 0) {
		dev_err(&client->dev, "unable to read reg %Xh, %d\n",
			AUO_PIXCIR_REG_INT_SETTING, ret);
		return ret;
	}

	ret &= ~AUO_PIXCIR_INT_MODE_MASK;
	ret |= int_setting;
	ret |= AUO_PIXCIR_INT_POL_HIGH; /* always use high for interrupts */

	ret = i2c_smbus_write_byte_data(client, AUO_PIXCIR_REG_INT_SETTING,
					ret);
	if (ret < 0) {
		dev_err(&client->dev, "unable to write reg %Xh, %d\n",
			AUO_PIXCIR_REG_INT_SETTING, ret);
		return ret;
	}

	ts->touch_ind_mode = pdata->int_setting == AUO_PIXCIR_INT_TOUCH_IND;

	return 0;
}