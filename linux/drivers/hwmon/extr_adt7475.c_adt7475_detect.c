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
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  REG_DEVID ; 
 int /*<<< orphan*/  REG_DEVID2 ; 
 int /*<<< orphan*/  REG_VENDID ; 
 int adt7475_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adt7475_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int vendid, devid, devid2;
	const char *name;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	vendid = adt7475_read(REG_VENDID);
	devid2 = adt7475_read(REG_DEVID2);
	if (vendid != 0x41 ||		/* Analog Devices */
	    (devid2 & 0xf8) != 0x68)
		return -ENODEV;

	devid = adt7475_read(REG_DEVID);
	if (devid == 0x73)
		name = "adt7473";
	else if (devid == 0x75 && client->addr == 0x2e)
		name = "adt7475";
	else if (devid == 0x76)
		name = "adt7476";
	else if ((devid2 & 0xfc) == 0x6c)
		name = "adt7490";
	else {
		dev_dbg(&adapter->dev,
			"Couldn't detect an ADT7473/75/76/90 part at "
			"0x%02x\n", (unsigned int)client->addr);
		return -ENODEV;
	}

	strlcpy(info->type, name, I2C_NAME_SIZE);

	return 0;
}