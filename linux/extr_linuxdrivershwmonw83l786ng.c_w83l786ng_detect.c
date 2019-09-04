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
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  W83L786NG_REG_CHIP_ID ; 
 int /*<<< orphan*/  W83L786NG_REG_CONFIG ; 
 int /*<<< orphan*/  W83L786NG_REG_MAN_ID1 ; 
 int /*<<< orphan*/  W83L786NG_REG_MAN_ID2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int w83l786ng_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
w83l786ng_detect(struct i2c_client *client, struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	u16 man_id;
	u8 chip_id;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* Detection */
	if ((w83l786ng_read_value(client, W83L786NG_REG_CONFIG) & 0x80)) {
		dev_dbg(&adapter->dev, "W83L786NG detection failed at 0x%02x\n",
			client->addr);
		return -ENODEV;
	}

	/* Identification */
	man_id = (w83l786ng_read_value(client, W83L786NG_REG_MAN_ID1) << 8) +
		 w83l786ng_read_value(client, W83L786NG_REG_MAN_ID2);
	chip_id = w83l786ng_read_value(client, W83L786NG_REG_CHIP_ID);

	if (man_id != 0x5CA3 ||		/* Winbond */
	    chip_id != 0x80) {		/* W83L786NG */
		dev_dbg(&adapter->dev,
			"Unsupported chip (man_id=0x%04X, chip_id=0x%02X)\n",
			man_id, chip_id);
		return -ENODEV;
	}

	strlcpy(info->type, "w83l786ng", I2C_NAME_SIZE);

	return 0;
}