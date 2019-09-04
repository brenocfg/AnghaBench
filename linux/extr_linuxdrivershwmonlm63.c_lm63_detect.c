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
struct i2c_client {int addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  LM63_REG_ALERT_MASK ; 
 int /*<<< orphan*/  LM63_REG_ALERT_STATUS ; 
 int /*<<< orphan*/  LM63_REG_CHIP_ID ; 
 int /*<<< orphan*/  LM63_REG_CONFIG1 ; 
 int /*<<< orphan*/  LM63_REG_CONFIG2 ; 
 int /*<<< orphan*/  LM63_REG_MAN_ID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm63_detect(struct i2c_client *client,
		       struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	u8 man_id, chip_id, reg_config1, reg_config2;
	u8 reg_alert_status, reg_alert_mask;
	int address = client->addr;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	man_id = i2c_smbus_read_byte_data(client, LM63_REG_MAN_ID);
	chip_id = i2c_smbus_read_byte_data(client, LM63_REG_CHIP_ID);

	reg_config1 = i2c_smbus_read_byte_data(client, LM63_REG_CONFIG1);
	reg_config2 = i2c_smbus_read_byte_data(client, LM63_REG_CONFIG2);
	reg_alert_status = i2c_smbus_read_byte_data(client,
			   LM63_REG_ALERT_STATUS);
	reg_alert_mask = i2c_smbus_read_byte_data(client, LM63_REG_ALERT_MASK);

	if (man_id != 0x01 /* National Semiconductor */
	 || (reg_config1 & 0x18) != 0x00
	 || (reg_config2 & 0xF8) != 0x00
	 || (reg_alert_status & 0x20) != 0x00
	 || (reg_alert_mask & 0xA4) != 0xA4) {
		dev_dbg(&adapter->dev,
			"Unsupported chip (man_id=0x%02X, chip_id=0x%02X)\n",
			man_id, chip_id);
		return -ENODEV;
	}

	if (chip_id == 0x41 && address == 0x4c)
		strlcpy(info->type, "lm63", I2C_NAME_SIZE);
	else if (chip_id == 0x51 && (address == 0x18 || address == 0x4e))
		strlcpy(info->type, "lm64", I2C_NAME_SIZE);
	else if (chip_id == 0x49 && address == 0x4c)
		strlcpy(info->type, "lm96163", I2C_NAME_SIZE);
	else
		return -ENODEV;

	return 0;
}