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
struct i2c_client {int /*<<< orphan*/  addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  SMSC47M192_REG_COMPANY_ID ; 
 int /*<<< orphan*/  SMSC47M192_REG_VERSION ; 
 int /*<<< orphan*/  SMSC47M192_REG_VID ; 
 int /*<<< orphan*/  SMSC47M192_REG_VID4 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smsc47m192_detect(struct i2c_client *client,
			     struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int version;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* Detection criteria from sensors_detect script */
	version = i2c_smbus_read_byte_data(client, SMSC47M192_REG_VERSION);
	if (i2c_smbus_read_byte_data(client,
				SMSC47M192_REG_COMPANY_ID) == 0x55
	 && (version & 0xf0) == 0x20
	 && (i2c_smbus_read_byte_data(client,
				SMSC47M192_REG_VID) & 0x70) == 0x00
	 && (i2c_smbus_read_byte_data(client,
				SMSC47M192_REG_VID4) & 0xfe) == 0x80) {
		dev_info(&adapter->dev,
			 "found SMSC47M192 or compatible, "
			 "version 2, stepping A%d\n", version & 0x0f);
	} else {
		dev_dbg(&adapter->dev,
			"SMSC47M192 detection failed at 0x%02x\n",
			client->addr);
		return -ENODEV;
	}

	strlcpy(info->type, "smsc47m192", I2C_NAME_SIZE);

	return 0;
}