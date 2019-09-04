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
struct i2c_client {unsigned short addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  W83792D_REG_BANK ; 
 int /*<<< orphan*/  W83792D_REG_CHIPMAN ; 
 int /*<<< orphan*/  W83792D_REG_CONFIG ; 
 int /*<<< orphan*/  W83792D_REG_I2C_ADDR ; 
 int /*<<< orphan*/  W83792D_REG_WCHIPID ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int w83792d_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83792d_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
w83792d_detect(struct i2c_client *client, struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int val1, val2;
	unsigned short address = client->addr;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	if (w83792d_read_value(client, W83792D_REG_CONFIG) & 0x80)
		return -ENODEV;

	val1 = w83792d_read_value(client, W83792D_REG_BANK);
	val2 = w83792d_read_value(client, W83792D_REG_CHIPMAN);
	/* Check for Winbond ID if in bank 0 */
	if (!(val1 & 0x07)) {  /* is Bank0 */
		if ((!(val1 & 0x80) && val2 != 0xa3) ||
		    ((val1 & 0x80) && val2 != 0x5c))
			return -ENODEV;
	}
	/*
	 * If Winbond chip, address of chip and W83792D_REG_I2C_ADDR
	 * should match
	 */
	if (w83792d_read_value(client, W83792D_REG_I2C_ADDR) != address)
		return -ENODEV;

	/*  Put it now into bank 0 and Vendor ID High Byte */
	w83792d_write_value(client,
			    W83792D_REG_BANK,
			    (w83792d_read_value(client,
				W83792D_REG_BANK) & 0x78) | 0x80);

	/* Determine the chip type. */
	val1 = w83792d_read_value(client, W83792D_REG_WCHIPID);
	val2 = w83792d_read_value(client, W83792D_REG_CHIPMAN);
	if (val1 != 0x7a || val2 != 0x5c)
		return -ENODEV;

	strlcpy(info->type, "w83792d", I2C_NAME_SIZE);

	return 0;
}