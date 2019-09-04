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
 int /*<<< orphan*/  LM83_REG_R_CHIP_ID ; 
 int /*<<< orphan*/  LM83_REG_R_CONFIG ; 
 int /*<<< orphan*/  LM83_REG_R_MAN_ID ; 
 int /*<<< orphan*/  LM83_REG_R_STATUS1 ; 
 int /*<<< orphan*/  LM83_REG_R_STATUS2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm83_detect(struct i2c_client *new_client,
		       struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = new_client->adapter;
	const char *name;
	u8 man_id, chip_id;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* Detection */
	if ((i2c_smbus_read_byte_data(new_client, LM83_REG_R_STATUS1) & 0xA8) ||
	    (i2c_smbus_read_byte_data(new_client, LM83_REG_R_STATUS2) & 0x48) ||
	    (i2c_smbus_read_byte_data(new_client, LM83_REG_R_CONFIG) & 0x41)) {
		dev_dbg(&adapter->dev, "LM83 detection failed at 0x%02x\n",
			new_client->addr);
		return -ENODEV;
	}

	/* Identification */
	man_id = i2c_smbus_read_byte_data(new_client, LM83_REG_R_MAN_ID);
	if (man_id != 0x01)	/* National Semiconductor */
		return -ENODEV;

	chip_id = i2c_smbus_read_byte_data(new_client, LM83_REG_R_CHIP_ID);
	switch (chip_id) {
	case 0x03:
		name = "lm83";
		break;
	case 0x01:
		name = "lm82";
		break;
	default:
		/* identification failed */
		dev_info(&adapter->dev,
			 "Unsupported chip (man_id=0x%02X, chip_id=0x%02X)\n",
			 man_id, chip_id);
		return -ENODEV;
	}

	strlcpy(info->type, name, I2C_NAME_SIZE);

	return 0;
}