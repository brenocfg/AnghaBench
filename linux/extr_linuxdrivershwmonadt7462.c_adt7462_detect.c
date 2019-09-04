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
 int ADT7462_DEVICE ; 
 int /*<<< orphan*/  ADT7462_REG_DEVICE ; 
 int /*<<< orphan*/  ADT7462_REG_REVISION ; 
 int /*<<< orphan*/  ADT7462_REG_VENDOR ; 
 int ADT7462_REVISION ; 
 int ADT7462_VENDOR ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adt7462_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int vendor, device, revision;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	vendor = i2c_smbus_read_byte_data(client, ADT7462_REG_VENDOR);
	if (vendor != ADT7462_VENDOR)
		return -ENODEV;

	device = i2c_smbus_read_byte_data(client, ADT7462_REG_DEVICE);
	if (device != ADT7462_DEVICE)
		return -ENODEV;

	revision = i2c_smbus_read_byte_data(client, ADT7462_REG_REVISION);
	if (revision != ADT7462_REVISION)
		return -ENODEV;

	strlcpy(info->type, "adt7462", I2C_NAME_SIZE);

	return 0;
}