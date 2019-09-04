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
struct i2c_client {int dummy; } ;
struct als_data {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 struct als_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int als_set_power_state(struct i2c_client *client, bool on_off)
{
	int ret_val;
	struct als_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->mutex);
	ret_val = i2c_smbus_read_byte_data(client, 0x80);
	if (ret_val < 0)
		goto fail;
	if (on_off)
		ret_val = ret_val | 0x01;
	else
		ret_val = ret_val & 0xFE;
	ret_val = i2c_smbus_write_byte_data(client, 0x80, ret_val);
fail:
	mutex_unlock(&data->mutex);
	return ret_val;
}