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
typedef  int u16 ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/  const) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int retu_regmap_read(void *context, const void *reg, size_t reg_size,
			    void *val, size_t val_size)
{
	int ret;
	struct device *dev = context;
	struct i2c_client *i2c = to_i2c_client(dev);

	BUG_ON(reg_size != 1 || val_size != 2);

	ret = i2c_smbus_read_word_data(i2c, *(u8 const *)reg);
	if (ret < 0)
		return ret;

	*(u16 *)val = ret;
	return 0;
}