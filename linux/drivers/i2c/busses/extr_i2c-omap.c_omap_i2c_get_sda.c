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
typedef  int u32 ;
struct omap_i2c_dev {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_I2C_SYSTEST_REG ; 
 int OMAP_I2C_SYSTEST_SDA_I_FUNC ; 
 struct omap_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int omap_i2c_read_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_i2c_get_sda(struct i2c_adapter *adap)
{
	struct omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 reg;

	reg = omap_i2c_read_reg(dev, OMAP_I2C_SYSTEST_REG);

	return reg & OMAP_I2C_SYSTEST_SDA_I_FUNC;
}