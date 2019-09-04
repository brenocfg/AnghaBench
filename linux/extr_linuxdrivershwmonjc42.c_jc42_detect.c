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
struct jc42_chips {int manid; int devid_mask; int devid; } ;
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct jc42_chips*) ; 
 int ENODEV ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  JC42_REG_CAP ; 
 int /*<<< orphan*/  JC42_REG_CONFIG ; 
 int /*<<< orphan*/  JC42_REG_DEVICEID ; 
 int /*<<< orphan*/  JC42_REG_MANID ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct jc42_chips* jc42_chips ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jc42_detect(struct i2c_client *client, struct i2c_board_info *info)
{
	struct i2c_adapter *adapter = client->adapter;
	int i, config, cap, manid, devid;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		return -ENODEV;

	cap = i2c_smbus_read_word_swapped(client, JC42_REG_CAP);
	config = i2c_smbus_read_word_swapped(client, JC42_REG_CONFIG);
	manid = i2c_smbus_read_word_swapped(client, JC42_REG_MANID);
	devid = i2c_smbus_read_word_swapped(client, JC42_REG_DEVICEID);

	if (cap < 0 || config < 0 || manid < 0 || devid < 0)
		return -ENODEV;

	if ((cap & 0xff00) || (config & 0xf800))
		return -ENODEV;

	for (i = 0; i < ARRAY_SIZE(jc42_chips); i++) {
		struct jc42_chips *chip = &jc42_chips[i];
		if (manid == chip->manid &&
		    (devid & chip->devid_mask) == chip->devid) {
			strlcpy(info->type, "jc42", I2C_NAME_SIZE);
			return 0;
		}
	}
	return -ENODEV;
}