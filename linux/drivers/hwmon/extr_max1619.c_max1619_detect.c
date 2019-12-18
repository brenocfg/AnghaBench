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
struct i2c_client {int /*<<< orphan*/  addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  MAX1619_REG_R_CHIP_ID ; 
 int /*<<< orphan*/  MAX1619_REG_R_CONFIG ; 
 int /*<<< orphan*/  MAX1619_REG_R_CONVRATE ; 
 int /*<<< orphan*/  MAX1619_REG_R_MAN_ID ; 
 int /*<<< orphan*/  MAX1619_REG_R_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max1619_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	u8 reg_config, reg_convrate, reg_status, man_id, chip_id;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* detection */
	reg_config = i2c_smbus_read_byte_data(client, MAX1619_REG_R_CONFIG);
	reg_convrate = i2c_smbus_read_byte_data(client, MAX1619_REG_R_CONVRATE);
	reg_status = i2c_smbus_read_byte_data(client, MAX1619_REG_R_STATUS);
	if ((reg_config & 0x03) != 0x00
	 || reg_convrate > 0x07 || (reg_status & 0x61) != 0x00) {
		dev_dbg(&adapter->dev, "MAX1619 detection failed at 0x%02x\n",
			client->addr);
		return -ENODEV;
	}

	/* identification */
	man_id = i2c_smbus_read_byte_data(client, MAX1619_REG_R_MAN_ID);
	chip_id = i2c_smbus_read_byte_data(client, MAX1619_REG_R_CHIP_ID);
	if (man_id != 0x4D || chip_id != 0x04) {
		dev_info(&adapter->dev,
			 "Unsupported chip (man_id=0x%02X, chip_id=0x%02X).\n",
			 man_id, chip_id);
		return -ENODEV;
	}

	strlcpy(info->type, "max1619", I2C_NAME_SIZE);

	return 0;
}