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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLM_GET_ADDR ; 
 int ENODEV ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int blinkm_read (struct i2c_client*,int /*<<< orphan*/ ,int*) ; 
 int blinkm_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int blinkm_detect(struct i2c_client *client, struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int ret;
	int count = 99;
	u8 tmpargs[7];

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_WORD_DATA
				     | I2C_FUNC_SMBUS_WRITE_BYTE))
		return -ENODEV;

	/* Now, we do the remaining detection. Simple for now. */
	/* We might need more guards to protect other i2c slaves */

	/* make sure the blinkM is balanced (read/writes) */
	while (count > 0) {
		ret = blinkm_write(client, BLM_GET_ADDR, NULL);
		if (ret)
			return ret;
		usleep_range(5000, 10000);
		ret = blinkm_read(client, BLM_GET_ADDR, tmpargs);
		if (ret)
			return ret;
		usleep_range(5000, 10000);
		if (tmpargs[0] == 0x09)
			count = 0;
		count--;
	}

	/* Step 1: Read BlinkM address back  -  cmd_char 'a' */
	ret = blinkm_write(client, BLM_GET_ADDR, NULL);
	if (ret < 0)
		return ret;
	usleep_range(20000, 30000);	/* allow a small delay */
	ret = blinkm_read(client, BLM_GET_ADDR, tmpargs);
	if (ret < 0)
		return ret;

	if (tmpargs[0] != 0x09) {
		dev_err(&client->dev, "enodev DEV ADDR = 0x%02X\n", tmpargs[0]);
		return -ENODEV;
	}

	strlcpy(info->type, "blinkm", I2C_NAME_SIZE);
	return 0;
}