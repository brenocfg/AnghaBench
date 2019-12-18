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
struct i2c_client {int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMC6W201_REG_COMPANY ; 
 int /*<<< orphan*/  EMC6W201_REG_CONFIG ; 
 int /*<<< orphan*/  EMC6W201_REG_VERSTEP ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emc6w201_detect(struct i2c_client *client,
			   struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int company, verstep, config;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* Identification */
	company = i2c_smbus_read_byte_data(client, EMC6W201_REG_COMPANY);
	if (company != 0x5C)
		return -ENODEV;
	verstep = i2c_smbus_read_byte_data(client, EMC6W201_REG_VERSTEP);
	if (verstep < 0 || (verstep & 0xF0) != 0xB0)
		return -ENODEV;
	if ((verstep & 0x0F) > 2) {
		dev_dbg(&client->dev, "Unknown EMC6W201 stepping %d\n",
			verstep & 0x0F);
		return -ENODEV;
	}

	/* Check configuration */
	config = i2c_smbus_read_byte_data(client, EMC6W201_REG_CONFIG);
	if (config < 0 || (config & 0xF4) != 0x04)
		return -ENODEV;
	if (!(config & 0x01)) {
		dev_err(&client->dev, "Monitoring not enabled\n");
		return -ENODEV;
	}

	strlcpy(info->type, "emc6w201", I2C_NAME_SIZE);

	return 0;
}