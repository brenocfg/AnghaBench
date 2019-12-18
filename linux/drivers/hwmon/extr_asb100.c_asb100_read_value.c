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
typedef  int u16 ;
struct i2c_client {int dummy; } ;
struct asb100_data {int /*<<< orphan*/  lock; struct i2c_client** lm75; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASB100_REG_BANK ; 
 struct asb100_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asb100_read_value(struct i2c_client *client, u16 reg)
{
	struct asb100_data *data = i2c_get_clientdata(client);
	struct i2c_client *cl;
	int res, bank;

	mutex_lock(&data->lock);

	bank = (reg >> 8) & 0x0f;
	if (bank > 2)
		/* switch banks */
		i2c_smbus_write_byte_data(client, ASB100_REG_BANK, bank);

	if (bank == 0 || bank > 2) {
		res = i2c_smbus_read_byte_data(client, reg & 0xff);
	} else {
		/* switch to subclient */
		cl = data->lm75[bank - 1];

		/* convert from ISA to LM75 I2C addresses */
		switch (reg & 0xff) {
		case 0x50: /* TEMP */
			res = i2c_smbus_read_word_swapped(cl, 0);
			break;
		case 0x52: /* CONFIG */
			res = i2c_smbus_read_byte_data(cl, 1);
			break;
		case 0x53: /* HYST */
			res = i2c_smbus_read_word_swapped(cl, 2);
			break;
		case 0x55: /* MAX */
		default:
			res = i2c_smbus_read_word_swapped(cl, 3);
			break;
		}
	}

	if (bank > 2)
		i2c_smbus_write_byte_data(client, ASB100_REG_BANK, 0);

	mutex_unlock(&data->lock);

	return res;
}