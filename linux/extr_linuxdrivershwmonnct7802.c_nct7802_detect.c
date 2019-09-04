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
struct i2c_client {int dummy; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  REG_BANK ; 
 int /*<<< orphan*/  REG_CHIP_ID ; 
 int /*<<< orphan*/  REG_TEMP_LSB ; 
 int /*<<< orphan*/  REG_TEMP_PECI_LSB ; 
 int /*<<< orphan*/  REG_VENDOR_ID ; 
 int /*<<< orphan*/  REG_VERSION_ID ; 
 int /*<<< orphan*/  REG_VOLTAGE_LOW ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nct7802_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	int reg;

	/*
	 * Chip identification registers are only available in bank 0,
	 * so only attempt chip detection if bank 0 is selected
	 */
	reg = i2c_smbus_read_byte_data(client, REG_BANK);
	if (reg != 0x00)
		return -ENODEV;

	reg = i2c_smbus_read_byte_data(client, REG_VENDOR_ID);
	if (reg != 0x50)
		return -ENODEV;

	reg = i2c_smbus_read_byte_data(client, REG_CHIP_ID);
	if (reg != 0xc3)
		return -ENODEV;

	reg = i2c_smbus_read_byte_data(client, REG_VERSION_ID);
	if (reg < 0 || (reg & 0xf0) != 0x20)
		return -ENODEV;

	/* Also validate lower bits of voltage and temperature registers */
	reg = i2c_smbus_read_byte_data(client, REG_TEMP_LSB);
	if (reg < 0 || (reg & 0x1f))
		return -ENODEV;

	reg = i2c_smbus_read_byte_data(client, REG_TEMP_PECI_LSB);
	if (reg < 0 || (reg & 0x3f))
		return -ENODEV;

	reg = i2c_smbus_read_byte_data(client, REG_VOLTAGE_LOW);
	if (reg < 0 || (reg & 0x3f))
		return -ENODEV;

	strlcpy(info->type, "nct7802", I2C_NAME_SIZE);
	return 0;
}