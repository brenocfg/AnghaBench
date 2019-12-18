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
 int /*<<< orphan*/  THERMAL_PID_REG ; 
 int /*<<< orphan*/  THERMAL_REVISION_REG ; 
 int /*<<< orphan*/  THERMAL_SMSC_ID_REG ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emc1403_detect(struct i2c_client *client,
			struct i2c_board_info *info)
{
	int id;
	/* Check if thermal chip is SMSC and EMC1403 or EMC1423 */

	id = i2c_smbus_read_byte_data(client, THERMAL_SMSC_ID_REG);
	if (id != 0x5d)
		return -ENODEV;

	id = i2c_smbus_read_byte_data(client, THERMAL_PID_REG);
	switch (id) {
	case 0x20:
		strlcpy(info->type, "emc1402", I2C_NAME_SIZE);
		break;
	case 0x21:
		strlcpy(info->type, "emc1403", I2C_NAME_SIZE);
		break;
	case 0x22:
		strlcpy(info->type, "emc1422", I2C_NAME_SIZE);
		break;
	case 0x23:
		strlcpy(info->type, "emc1423", I2C_NAME_SIZE);
		break;
	case 0x25:
		strlcpy(info->type, "emc1404", I2C_NAME_SIZE);
		break;
	case 0x27:
		strlcpy(info->type, "emc1424", I2C_NAME_SIZE);
		break;
	default:
		return -ENODEV;
	}

	id = i2c_smbus_read_byte_data(client, THERMAL_REVISION_REG);
	if (id < 0x01 || id > 0x04)
		return -ENODEV;

	return 0;
}