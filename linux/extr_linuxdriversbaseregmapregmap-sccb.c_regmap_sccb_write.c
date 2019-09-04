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
struct device {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (struct i2c_client*,unsigned int,unsigned int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int regmap_sccb_write(void *context, unsigned int reg, unsigned int val)
{
	struct device *dev = context;
	struct i2c_client *i2c = to_i2c_client(dev);

	return i2c_smbus_write_byte_data(i2c, reg, val);
}