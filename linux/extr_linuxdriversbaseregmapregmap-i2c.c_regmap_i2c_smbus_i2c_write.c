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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int i2c_smbus_write_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int regmap_i2c_smbus_i2c_write(void *context, const void *data,
				      size_t count)
{
	struct device *dev = context;
	struct i2c_client *i2c = to_i2c_client(dev);

	if (count < 1)
		return -EINVAL;

	--count;
	return i2c_smbus_write_i2c_block_data(i2c, ((u8 *)data)[0], count,
					      ((u8 *)data + 1));
}