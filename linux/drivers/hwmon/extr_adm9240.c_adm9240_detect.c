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
struct i2c_client {int addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM9240_REG_DIE_REV ; 
 int /*<<< orphan*/  ADM9240_REG_I2C_ADDR ; 
 int /*<<< orphan*/  ADM9240_REG_MAN_ID ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm9240_detect(struct i2c_client *new_client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = new_client->adapter;
	const char *name = "";
	int address = new_client->addr;
	u8 man_id, die_rev;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* verify chip: reg address should match i2c address */
	if (i2c_smbus_read_byte_data(new_client, ADM9240_REG_I2C_ADDR)
			!= address) {
		dev_err(&adapter->dev, "detect fail: address match, 0x%02x\n",
			address);
		return -ENODEV;
	}

	/* check known chip manufacturer */
	man_id = i2c_smbus_read_byte_data(new_client, ADM9240_REG_MAN_ID);
	if (man_id == 0x23) {
		name = "adm9240";
	} else if (man_id == 0xda) {
		name = "ds1780";
	} else if (man_id == 0x01) {
		name = "lm81";
	} else {
		dev_err(&adapter->dev, "detect fail: unknown manuf, 0x%02x\n",
			man_id);
		return -ENODEV;
	}

	/* successful detect, print chip info */
	die_rev = i2c_smbus_read_byte_data(new_client, ADM9240_REG_DIE_REV);
	dev_info(&adapter->dev, "found %s revision %u\n",
		 man_id == 0x23 ? "ADM9240" :
		 man_id == 0xda ? "DS1780" : "LM81", die_rev);

	strlcpy(info->type, name, I2C_NAME_SIZE);

	return 0;
}