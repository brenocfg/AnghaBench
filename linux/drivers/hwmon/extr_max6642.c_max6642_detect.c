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
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int MAX6642_REG_R_CONFIG ; 
 int MAX6642_REG_R_MAN_ID ; 
 int MAX6642_REG_R_STATUS ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max6642_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	u8 reg_config, reg_status, man_id;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* identification */
	man_id = i2c_smbus_read_byte_data(client, MAX6642_REG_R_MAN_ID);
	if (man_id != 0x4D)
		return -ENODEV;

	/* sanity check */
	if (i2c_smbus_read_byte_data(client, 0x04) != 0x4D
	    || i2c_smbus_read_byte_data(client, 0x06) != 0x4D
	    || i2c_smbus_read_byte_data(client, 0xff) != 0x4D)
		return -ENODEV;

	/*
	 * We read the config and status register, the 4 lower bits in the
	 * config register should be zero and bit 5, 3, 1 and 0 should be
	 * zero in the status register.
	 */
	reg_config = i2c_smbus_read_byte_data(client, MAX6642_REG_R_CONFIG);
	if ((reg_config & 0x0f) != 0x00)
		return -ENODEV;

	/* in between, another round of sanity checks */
	if (i2c_smbus_read_byte_data(client, 0x04) != reg_config
	    || i2c_smbus_read_byte_data(client, 0x06) != reg_config
	    || i2c_smbus_read_byte_data(client, 0xff) != reg_config)
		return -ENODEV;

	reg_status = i2c_smbus_read_byte_data(client, MAX6642_REG_R_STATUS);
	if ((reg_status & 0x2b) != 0x00)
		return -ENODEV;

	strlcpy(info->type, "max6642", I2C_NAME_SIZE);

	return 0;
}