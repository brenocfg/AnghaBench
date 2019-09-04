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
struct max8997_dev {int /*<<< orphan*/  iolock; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct max8997_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int max8997_read_reg(struct i2c_client *i2c, u8 reg, u8 *dest)
{
	struct max8997_dev *max8997 = i2c_get_clientdata(i2c);
	int ret;

	mutex_lock(&max8997->iolock);
	ret = i2c_smbus_read_byte_data(i2c, reg);
	mutex_unlock(&max8997->iolock);
	if (ret < 0)
		return ret;

	ret &= 0xff;
	*dest = ret;
	return 0;
}