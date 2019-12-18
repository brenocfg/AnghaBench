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
struct w83792d_data {TYPE_1__** lm75; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  W83792D_REG_I2C_SUBADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* devm_i2c_new_dummy_device (int /*<<< orphan*/ *,struct i2c_adapter*,int) ; 
 int* force_subclients ; 
 int i2c_adapter_id (struct i2c_adapter*) ; 
 struct w83792d_data* i2c_get_clientdata (struct i2c_client*) ; 
 int w83792d_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83792d_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
w83792d_detect_subclients(struct i2c_client *new_client)
{
	int i, id;
	int address = new_client->addr;
	u8 val;
	struct i2c_adapter *adapter = new_client->adapter;
	struct w83792d_data *data = i2c_get_clientdata(new_client);

	id = i2c_adapter_id(adapter);
	if (force_subclients[0] == id && force_subclients[1] == address) {
		for (i = 2; i <= 3; i++) {
			if (force_subclients[i] < 0x48 ||
			    force_subclients[i] > 0x4f) {
				dev_err(&new_client->dev,
					"invalid subclient address %d; must be 0x48-0x4f\n",
					force_subclients[i]);
				return -ENODEV;
			}
		}
		w83792d_write_value(new_client, W83792D_REG_I2C_SUBADDR,
					(force_subclients[2] & 0x07) |
					((force_subclients[3] & 0x07) << 4));
	}

	val = w83792d_read_value(new_client, W83792D_REG_I2C_SUBADDR);
	if (!(val & 0x08))
		data->lm75[0] = devm_i2c_new_dummy_device(&new_client->dev, adapter,
							  0x48 + (val & 0x7));
	if (!(val & 0x80)) {
		if (!IS_ERR(data->lm75[0]) &&
			((val & 0x7) == ((val >> 4) & 0x7))) {
			dev_err(&new_client->dev,
				"duplicate addresses 0x%x, use force_subclient\n",
				data->lm75[0]->addr);
			return -ENODEV;
		}
		data->lm75[1] = devm_i2c_new_dummy_device(&new_client->dev, adapter,
							  0x48 + ((val >> 4) & 0x7));
	}

	return 0;
}