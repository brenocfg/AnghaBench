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
typedef  int u8 ;
struct i2c_client {int addr; struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
typedef  enum chips { ____Placeholder_chips } chips ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  TMP401_CONFIG_READ ; 
 int /*<<< orphan*/  TMP401_CONVERSION_RATE_READ ; 
#define  TMP401_DEVICE_ID 134 
 int /*<<< orphan*/  TMP401_DEVICE_ID_REG ; 
 int TMP401_MANUFACTURER_ID ; 
 int /*<<< orphan*/  TMP401_MANUFACTURER_ID_REG ; 
#define  TMP411A_DEVICE_ID 133 
#define  TMP411B_DEVICE_ID 132 
#define  TMP411C_DEVICE_ID 131 
#define  TMP431_DEVICE_ID 130 
#define  TMP432_DEVICE_ID 129 
#define  TMP435_DEVICE_ID 128 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tmp401 ; 
 TYPE_1__* tmp401_id ; 
 int tmp411 ; 
 int tmp431 ; 
 int tmp432 ; 
 int tmp435 ; 

__attribute__((used)) static int tmp401_detect(struct i2c_client *client,
			 struct i2c_board_info *info)
{
	enum chips kind;
	struct i2c_adapter *adapter = client->adapter;
	u8 reg;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/* Detect and identify the chip */
	reg = i2c_smbus_read_byte_data(client, TMP401_MANUFACTURER_ID_REG);
	if (reg != TMP401_MANUFACTURER_ID)
		return -ENODEV;

	reg = i2c_smbus_read_byte_data(client, TMP401_DEVICE_ID_REG);

	switch (reg) {
	case TMP401_DEVICE_ID:
		if (client->addr != 0x4c)
			return -ENODEV;
		kind = tmp401;
		break;
	case TMP411A_DEVICE_ID:
		if (client->addr != 0x4c)
			return -ENODEV;
		kind = tmp411;
		break;
	case TMP411B_DEVICE_ID:
		if (client->addr != 0x4d)
			return -ENODEV;
		kind = tmp411;
		break;
	case TMP411C_DEVICE_ID:
		if (client->addr != 0x4e)
			return -ENODEV;
		kind = tmp411;
		break;
	case TMP431_DEVICE_ID:
		if (client->addr != 0x4c && client->addr != 0x4d)
			return -ENODEV;
		kind = tmp431;
		break;
	case TMP432_DEVICE_ID:
		if (client->addr != 0x4c && client->addr != 0x4d)
			return -ENODEV;
		kind = tmp432;
		break;
	case TMP435_DEVICE_ID:
		kind = tmp435;
		break;
	default:
		return -ENODEV;
	}

	reg = i2c_smbus_read_byte_data(client, TMP401_CONFIG_READ);
	if (reg & 0x1b)
		return -ENODEV;

	reg = i2c_smbus_read_byte_data(client, TMP401_CONVERSION_RATE_READ);
	/* Datasheet says: 0x1-0x6 */
	if (reg > 15)
		return -ENODEV;

	strlcpy(info->type, tmp401_id[kind].name, I2C_NAME_SIZE);

	return 0;
}