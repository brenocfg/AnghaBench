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
struct w83795_data {int bank; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  W83795_REG_BANKSEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 struct w83795_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int w83795_set_bank(struct i2c_client *client, u8 bank)
{
	struct w83795_data *data = i2c_get_clientdata(client);
	int err;

	/* If the same bank is already set, nothing to do */
	if ((data->bank & 0x07) == bank)
		return 0;

	/* Change to new bank, preserve all other bits */
	bank |= data->bank & ~0x07;
	err = i2c_smbus_write_byte_data(client, W83795_REG_BANKSEL, bank);
	if (err < 0) {
		dev_err(&client->dev,
			"Failed to set bank to %d, err %d\n",
			(int)bank, err);
		return err;
	}
	data->bank = bank;

	return 0;
}