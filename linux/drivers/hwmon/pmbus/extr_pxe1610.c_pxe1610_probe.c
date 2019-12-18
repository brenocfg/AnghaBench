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
typedef  int /*<<< orphan*/  u8 ;
struct pmbus_driver_info {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_READ_BLOCK_DATA ; 
 int I2C_FUNC_SMBUS_READ_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_READ_WORD_DATA ; 
 int I2C_SMBUS_BLOCK_MAX ; 
 int /*<<< orphan*/  PMBUS_MFR_ID ; 
 int /*<<< orphan*/  PMBUS_PAGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct pmbus_driver_info* devm_kmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_block_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmbus_do_probe (struct i2c_client*,struct i2c_device_id const*,struct pmbus_driver_info*) ; 
 int /*<<< orphan*/  pxe1610_info ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int pxe1610_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct pmbus_driver_info *info;
	u8 buf[I2C_SMBUS_BLOCK_MAX];
	int ret;

	if (!i2c_check_functionality(
			client->adapter,
			I2C_FUNC_SMBUS_READ_BYTE_DATA
			| I2C_FUNC_SMBUS_READ_WORD_DATA
			| I2C_FUNC_SMBUS_READ_BLOCK_DATA))
		return -ENODEV;

	/*
	 * By default this device doesn't boot to page 0, so set page 0
	 * to access all pmbus registers.
	 */
	i2c_smbus_write_byte_data(client, PMBUS_PAGE, 0);

	/* Read Manufacturer id */
	ret = i2c_smbus_read_block_data(client, PMBUS_MFR_ID, buf);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to read PMBUS_MFR_ID\n");
		return ret;
	}
	if (ret != 2 || strncmp(buf, "XP", 2)) {
		dev_err(&client->dev, "MFR_ID unrecognized\n");
		return -ENODEV;
	}

	info = devm_kmemdup(&client->dev, &pxe1610_info,
			    sizeof(struct pmbus_driver_info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	return pmbus_do_probe(client, id, info);
}