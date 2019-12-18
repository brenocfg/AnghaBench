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
 int /*<<< orphan*/  W83791D_REG_BANK ; 
 int /*<<< orphan*/  W83791D_REG_CHIPMAN ; 
 int /*<<< orphan*/  W83791D_REG_CONFIG ; 
 int /*<<< orphan*/  W83791D_REG_I2C_ADDR ; 
 int /*<<< orphan*/  W83791D_REG_WCHIPID ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int w83791d_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83791d_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int w83791d_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int val1, val2;
	unsigned short address = client->addr;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	if (w83791d_read(client, W83791D_REG_CONFIG) & 0x80)
		return -ENODEV;

	val1 = w83791d_read(client, W83791D_REG_BANK);
	val2 = w83791d_read(client, W83791D_REG_CHIPMAN);
	/* Check for Winbond ID if in bank 0 */
	if (!(val1 & 0x07)) {
		if ((!(val1 & 0x80) && val2 != 0xa3) ||
		    ((val1 & 0x80) && val2 != 0x5c)) {
			return -ENODEV;
		}
	}
	/*
	 * If Winbond chip, address of chip and W83791D_REG_I2C_ADDR
	 * should match
	 */
	if (w83791d_read(client, W83791D_REG_I2C_ADDR) != address)
		return -ENODEV;

	/* We want bank 0 and Vendor ID high byte */
	val1 = w83791d_read(client, W83791D_REG_BANK) & 0x78;
	w83791d_write(client, W83791D_REG_BANK, val1 | 0x80);

	/* Verify it is a Winbond w83791d */
	val1 = w83791d_read(client, W83791D_REG_WCHIPID);
	val2 = w83791d_read(client, W83791D_REG_CHIPMAN);
	if (val1 != 0x71 || val2 != 0x5c)
		return -ENODEV;

	strlcpy(info->type, "w83791d", I2C_NAME_SIZE);

	return 0;
}