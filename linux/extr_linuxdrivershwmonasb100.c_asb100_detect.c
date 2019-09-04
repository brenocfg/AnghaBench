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
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASB100_REG_BANK ; 
 int /*<<< orphan*/  ASB100_REG_CHIPMAN ; 
 int /*<<< orphan*/  ASB100_REG_WCHIPID ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asb100_detect(struct i2c_client *client,
			 struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int val1, val2;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		pr_debug("detect failed, smbus byte data not supported!\n");
		return -ENODEV;
	}

	val1 = i2c_smbus_read_byte_data(client, ASB100_REG_BANK);
	val2 = i2c_smbus_read_byte_data(client, ASB100_REG_CHIPMAN);

	/* If we're in bank 0 */
	if ((!(val1 & 0x07)) &&
			/* Check for ASB100 ID (low byte) */
			(((!(val1 & 0x80)) && (val2 != 0x94)) ||
			/* Check for ASB100 ID (high byte ) */
			((val1 & 0x80) && (val2 != 0x06)))) {
		pr_debug("detect failed, bad chip id 0x%02x!\n", val2);
		return -ENODEV;
	}

	/* Put it now into bank 0 and Vendor ID High Byte */
	i2c_smbus_write_byte_data(client, ASB100_REG_BANK,
		(i2c_smbus_read_byte_data(client, ASB100_REG_BANK) & 0x78)
		| 0x80);

	/* Determine the chip type. */
	val1 = i2c_smbus_read_byte_data(client, ASB100_REG_WCHIPID);
	val2 = i2c_smbus_read_byte_data(client, ASB100_REG_CHIPMAN);

	if (val1 != 0x31 || val2 != 0x06)
		return -ENODEV;

	strlcpy(info->type, "asb100", I2C_NAME_SIZE);

	return 0;
}