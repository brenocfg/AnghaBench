#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
#define  STTS751_0_PROD_ID 129 
#define  STTS751_1_PROD_ID 128 
 int /*<<< orphan*/  STTS751_REG_HLIM_L ; 
 int /*<<< orphan*/  STTS751_REG_LLIM_L ; 
 int /*<<< orphan*/  STTS751_REG_MAN_ID ; 
 int /*<<< orphan*/  STTS751_REG_PROD_ID ; 
 int /*<<< orphan*/  STTS751_REG_SMBUS_TO ; 
 int /*<<< orphan*/  STTS751_REG_TEMP_L ; 
 int ST_MAN_ID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* stts751_id ; 

__attribute__((used)) static int stts751_detect(struct i2c_client *new_client,
			  struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = new_client->adapter;
	const char *name;
	int tmp;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	tmp = i2c_smbus_read_byte_data(new_client, STTS751_REG_MAN_ID);
	if (tmp != ST_MAN_ID)
		return -ENODEV;

	/* lower temperaure registers always have bits 0-3 set to zero */
	tmp = i2c_smbus_read_byte_data(new_client, STTS751_REG_TEMP_L);
	if (tmp & 0xf)
		return -ENODEV;

	tmp = i2c_smbus_read_byte_data(new_client, STTS751_REG_HLIM_L);
	if (tmp & 0xf)
		return -ENODEV;

	tmp = i2c_smbus_read_byte_data(new_client, STTS751_REG_LLIM_L);
	if (tmp & 0xf)
		return -ENODEV;

	/* smbus timeout register always have bits 0-7 set to zero */
	tmp = i2c_smbus_read_byte_data(new_client, STTS751_REG_SMBUS_TO);
	if (tmp & 0x7f)
		return -ENODEV;

	tmp = i2c_smbus_read_byte_data(new_client, STTS751_REG_PROD_ID);

	switch (tmp) {
	case STTS751_0_PROD_ID:
		name = "STTS751-0";
		break;
	case STTS751_1_PROD_ID:
		name = "STTS751-1";
		break;
	default:
		return -ENODEV;
	}
	dev_dbg(&new_client->dev, "Chip %s detected", name);

	strlcpy(info->type, stts751_id[0].name, I2C_NAME_SIZE);
	return 0;
}