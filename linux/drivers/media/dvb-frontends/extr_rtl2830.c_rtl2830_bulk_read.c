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
struct rtl2830_dev {int /*<<< orphan*/  regmap; } ;
struct i2c_client {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_LOCK_SEGMENT ; 
 struct rtl2830_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_lock_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unlock_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,unsigned int,void*,size_t) ; 

__attribute__((used)) static int rtl2830_bulk_read(struct i2c_client *client, unsigned int reg,
			     void *val, size_t val_count)
{
	struct rtl2830_dev *dev = i2c_get_clientdata(client);
	int ret;

	i2c_lock_bus(client->adapter, I2C_LOCK_SEGMENT);
	ret = regmap_bulk_read(dev->regmap, reg, val, val_count);
	i2c_unlock_bus(client->adapter, I2C_LOCK_SEGMENT);
	return ret;
}