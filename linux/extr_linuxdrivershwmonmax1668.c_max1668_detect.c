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
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int DEV_ID_MAX1668 ; 
 int DEV_ID_MAX1805 ; 
 int DEV_ID_MAX1989 ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int MAN_ID_MAXIM ; 
 int /*<<< orphan*/  MAX1668_REG_DEV_ID ; 
 int /*<<< orphan*/  MAX1668_REG_MAN_ID ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max1668_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	const char *type_name;
	int man_id, dev_id;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* Check for unsupported part */
	man_id = i2c_smbus_read_byte_data(client, MAX1668_REG_MAN_ID);
	if (man_id != MAN_ID_MAXIM)
		return -ENODEV;

	dev_id = i2c_smbus_read_byte_data(client, MAX1668_REG_DEV_ID);
	if (dev_id < 0)
		return -ENODEV;

	type_name = NULL;
	if (dev_id == DEV_ID_MAX1668)
		type_name = "max1668";
	else if (dev_id == DEV_ID_MAX1805)
		type_name = "max1805";
	else if (dev_id == DEV_ID_MAX1989)
		type_name = "max1989";

	if (!type_name)
		return -ENODEV;

	strlcpy(info->type, type_name, I2C_NAME_SIZE);

	return 0;
}