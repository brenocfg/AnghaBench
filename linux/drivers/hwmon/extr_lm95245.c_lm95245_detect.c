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
struct i2c_client {int addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
#define  LM95235_REVISION 129 
 int /*<<< orphan*/  LM95245_REG_R_CHIP_ID ; 
 int /*<<< orphan*/  LM95245_REG_R_MAN_ID ; 
#define  LM95245_REVISION 128 
 int MANUFACTURER_ID ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm95245_detect(struct i2c_client *new_client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = new_client->adapter;
	int address = new_client->addr;
	const char *name;
	int rev, id;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	id = i2c_smbus_read_byte_data(new_client, LM95245_REG_R_MAN_ID);
	if (id != MANUFACTURER_ID)
		return -ENODEV;

	rev = i2c_smbus_read_byte_data(new_client, LM95245_REG_R_CHIP_ID);
	switch (rev) {
	case LM95235_REVISION:
		if (address != 0x18 && address != 0x29 && address != 0x4c)
			return -ENODEV;
		name = "lm95235";
		break;
	case LM95245_REVISION:
		name = "lm95245";
		break;
	default:
		return -ENODEV;
	}

	strlcpy(info->type, name, I2C_NAME_SIZE);
	return 0;
}