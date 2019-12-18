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
 int LM85_COMPANY_ANALOG_DEV ; 
 int LM85_COMPANY_NATIONAL ; 
 int LM85_COMPANY_SMSC ; 
 int /*<<< orphan*/  LM85_REG_COMPANY ; 
 int /*<<< orphan*/  LM85_REG_VERSTEP ; 
#define  LM85_VERSTEP_ADM1027 142 
#define  LM85_VERSTEP_ADT7463 141 
#define  LM85_VERSTEP_ADT7463C 140 
#define  LM85_VERSTEP_ADT7468_1 139 
#define  LM85_VERSTEP_ADT7468_2 138 
#define  LM85_VERSTEP_EMC6D100_A0 137 
#define  LM85_VERSTEP_EMC6D100_A1 136 
#define  LM85_VERSTEP_EMC6D102 135 
#define  LM85_VERSTEP_EMC6D103S 134 
#define  LM85_VERSTEP_EMC6D103_A0 133 
#define  LM85_VERSTEP_EMC6D103_A1 132 
#define  LM85_VERSTEP_LM85B 131 
#define  LM85_VERSTEP_LM85C 130 
#define  LM85_VERSTEP_LM96000_1 129 
#define  LM85_VERSTEP_LM96000_2 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm85_is_fake (struct i2c_client*) ; 
 int lm85_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm85_detect(struct i2c_client *client, struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int address = client->addr;
	const char *type_name = NULL;
	int company, verstep;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		/* We need to be able to do byte I/O */
		return -ENODEV;
	}

	/* Determine the chip type */
	company = lm85_read_value(client, LM85_REG_COMPANY);
	verstep = lm85_read_value(client, LM85_REG_VERSTEP);

	dev_dbg(&adapter->dev,
		"Detecting device at 0x%02x with COMPANY: 0x%02x and VERSTEP: 0x%02x\n",
		address, company, verstep);

	if (company == LM85_COMPANY_NATIONAL) {
		switch (verstep) {
		case LM85_VERSTEP_LM85C:
			type_name = "lm85c";
			break;
		case LM85_VERSTEP_LM85B:
			type_name = "lm85b";
			break;
		case LM85_VERSTEP_LM96000_1:
		case LM85_VERSTEP_LM96000_2:
			/* Check for Winbond WPCD377I */
			if (lm85_is_fake(client)) {
				dev_dbg(&adapter->dev,
					"Found Winbond WPCD377I, ignoring\n");
				return -ENODEV;
			}
			type_name = "lm96000";
			break;
		}
	} else if (company == LM85_COMPANY_ANALOG_DEV) {
		switch (verstep) {
		case LM85_VERSTEP_ADM1027:
			type_name = "adm1027";
			break;
		case LM85_VERSTEP_ADT7463:
		case LM85_VERSTEP_ADT7463C:
			type_name = "adt7463";
			break;
		case LM85_VERSTEP_ADT7468_1:
		case LM85_VERSTEP_ADT7468_2:
			type_name = "adt7468";
			break;
		}
	} else if (company == LM85_COMPANY_SMSC) {
		switch (verstep) {
		case LM85_VERSTEP_EMC6D100_A0:
		case LM85_VERSTEP_EMC6D100_A1:
			/* Note: we can't tell a '100 from a '101 */
			type_name = "emc6d100";
			break;
		case LM85_VERSTEP_EMC6D102:
			type_name = "emc6d102";
			break;
		case LM85_VERSTEP_EMC6D103_A0:
		case LM85_VERSTEP_EMC6D103_A1:
			type_name = "emc6d103";
			break;
		case LM85_VERSTEP_EMC6D103S:
			type_name = "emc6d103s";
			break;
		}
	}

	if (!type_name)
		return -ENODEV;

	strlcpy(info->type, type_name, I2C_NAME_SIZE);

	return 0;
}