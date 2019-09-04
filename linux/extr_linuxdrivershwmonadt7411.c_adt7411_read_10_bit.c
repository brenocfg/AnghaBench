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
struct i2c_client {int dummy; } ;
struct adt7411_data {int /*<<< orphan*/  device_lock; } ;

/* Variables and functions */
 struct adt7411_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adt7411_read_10_bit(struct i2c_client *client, u8 lsb_reg,
				u8 msb_reg, u8 lsb_shift)
{
	struct adt7411_data *data = i2c_get_clientdata(client);
	int val, tmp;

	mutex_lock(&data->device_lock);

	val = i2c_smbus_read_byte_data(client, lsb_reg);
	if (val < 0)
		goto exit_unlock;

	tmp = (val >> lsb_shift) & 3;
	val = i2c_smbus_read_byte_data(client, msb_reg);

	if (val >= 0)
		val = (val << 2) | tmp;

 exit_unlock:
	mutex_unlock(&data->device_lock);

	return val;
}