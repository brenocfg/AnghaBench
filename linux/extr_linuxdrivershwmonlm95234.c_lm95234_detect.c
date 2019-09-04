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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
#define  LM95233_CHIP_ID 129 
#define  LM95234_CHIP_ID 128 
 int /*<<< orphan*/  LM95234_REG_CHIP_ID ; 
 int /*<<< orphan*/  LM95234_REG_CONFIG ; 
 int /*<<< orphan*/  LM95234_REG_CONVRATE ; 
 int /*<<< orphan*/  LM95234_REG_MAN_ID ; 
 int /*<<< orphan*/  LM95234_REG_REM_MODEL ; 
 int /*<<< orphan*/  LM95234_REG_REM_MODEL_STS ; 
 int /*<<< orphan*/  LM95234_REG_STATUS ; 
 int NATSEMI_MAN_ID ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm95234_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int address = client->addr;
	u8 config_mask, model_mask;
	int mfg_id, chip_id, val;
	const char *name;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	mfg_id = i2c_smbus_read_byte_data(client, LM95234_REG_MAN_ID);
	if (mfg_id != NATSEMI_MAN_ID)
		return -ENODEV;

	chip_id = i2c_smbus_read_byte_data(client, LM95234_REG_CHIP_ID);
	switch (chip_id) {
	case LM95233_CHIP_ID:
		if (address != 0x18 && address != 0x2a && address != 0x2b)
			return -ENODEV;
		config_mask = 0xbf;
		model_mask = 0xf9;
		name = "lm95233";
		break;
	case LM95234_CHIP_ID:
		if (address != 0x18 && address != 0x4d && address != 0x4e)
			return -ENODEV;
		config_mask = 0xbc;
		model_mask = 0xe1;
		name = "lm95234";
		break;
	default:
		return -ENODEV;
	}

	val = i2c_smbus_read_byte_data(client, LM95234_REG_STATUS);
	if (val & 0x30)
		return -ENODEV;

	val = i2c_smbus_read_byte_data(client, LM95234_REG_CONFIG);
	if (val & config_mask)
		return -ENODEV;

	val = i2c_smbus_read_byte_data(client, LM95234_REG_CONVRATE);
	if (val & 0xfc)
		return -ENODEV;

	val = i2c_smbus_read_byte_data(client, LM95234_REG_REM_MODEL);
	if (val & model_mask)
		return -ENODEV;

	val = i2c_smbus_read_byte_data(client, LM95234_REG_REM_MODEL_STS);
	if (val & model_mask)
		return -ENODEV;

	strlcpy(info->type, name, I2C_NAME_SIZE);
	return 0;
}