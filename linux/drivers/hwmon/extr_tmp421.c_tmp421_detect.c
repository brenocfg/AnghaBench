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
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
typedef  enum chips { ____Placeholder_chips } chips ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  TMP421_CONVERSION_RATE_REG ; 
#define  TMP421_DEVICE_ID 132 
 int /*<<< orphan*/  TMP421_DEVICE_ID_REG ; 
 int TMP421_MANUFACTURER_ID ; 
 int /*<<< orphan*/  TMP421_MANUFACTURER_ID_REG ; 
 int /*<<< orphan*/  TMP421_STATUS_REG ; 
#define  TMP422_DEVICE_ID 131 
#define  TMP423_DEVICE_ID 130 
#define  TMP441_DEVICE_ID 129 
#define  TMP442_DEVICE_ID 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const* const,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tmp421 ; 
 TYPE_1__* tmp421_id ; 
 int tmp422 ; 
 int tmp423 ; 
 int tmp441 ; 
 int tmp442 ; 

__attribute__((used)) static int tmp421_detect(struct i2c_client *client,
			 struct i2c_board_info *info)
{
	enum chips kind;
	struct i2c_adapter *adapter = client->adapter;
	static const char * const names[] = {
		"TMP421", "TMP422", "TMP423",
		"TMP441", "TMP442"
	};
	int addr = client->addr;
	u8 reg;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	reg = i2c_smbus_read_byte_data(client, TMP421_MANUFACTURER_ID_REG);
	if (reg != TMP421_MANUFACTURER_ID)
		return -ENODEV;

	reg = i2c_smbus_read_byte_data(client, TMP421_CONVERSION_RATE_REG);
	if (reg & 0xf8)
		return -ENODEV;

	reg = i2c_smbus_read_byte_data(client, TMP421_STATUS_REG);
	if (reg & 0x7f)
		return -ENODEV;

	reg = i2c_smbus_read_byte_data(client, TMP421_DEVICE_ID_REG);
	switch (reg) {
	case TMP421_DEVICE_ID:
		kind = tmp421;
		break;
	case TMP422_DEVICE_ID:
		if (addr == 0x2a)
			return -ENODEV;
		kind = tmp422;
		break;
	case TMP423_DEVICE_ID:
		if (addr != 0x4c && addr != 0x4d)
			return -ENODEV;
		kind = tmp423;
		break;
	case TMP441_DEVICE_ID:
		kind = tmp441;
		break;
	case TMP442_DEVICE_ID:
		if (addr != 0x4c && addr != 0x4d)
			return -ENODEV;
		kind = tmp442;
		break;
	default:
		return -ENODEV;
	}

	strlcpy(info->type, tmp421_id[kind].name, I2C_NAME_SIZE);
	dev_info(&adapter->dev, "Detected TI %s chip at 0x%02x\n",
		 names[kind], client->addr);

	return 0;
}