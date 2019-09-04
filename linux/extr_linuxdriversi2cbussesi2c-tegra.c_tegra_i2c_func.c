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
typedef  int u32 ;
struct tegra_i2c_dev {TYPE_1__* hw; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {scalar_t__ has_continue_xfer_support; } ;

/* Variables and functions */
 int I2C_FUNC_10BIT_ADDR ; 
 int I2C_FUNC_I2C ; 
 int I2C_FUNC_NOSTART ; 
 int I2C_FUNC_PROTOCOL_MANGLING ; 
 int I2C_FUNC_SMBUS_EMUL ; 
 int I2C_FUNC_SMBUS_QUICK ; 
 struct tegra_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static u32 tegra_i2c_func(struct i2c_adapter *adap)
{
	struct tegra_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	u32 ret = I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK) |
		  I2C_FUNC_10BIT_ADDR |	I2C_FUNC_PROTOCOL_MANGLING;

	if (i2c_dev->hw->has_continue_xfer_support)
		ret |= I2C_FUNC_NOSTART;
	return ret;
}