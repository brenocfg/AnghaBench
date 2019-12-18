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
typedef  int /*<<< orphan*/  u32 ;
struct omap_i2c_dev {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_I2C_SYSTEST_REG ; 
 int /*<<< orphan*/  OMAP_I2C_SYSTEST_SCL_O ; 
 int /*<<< orphan*/  OMAP_I2C_SYSTEST_SDA_O ; 
 int /*<<< orphan*/  OMAP_I2C_SYSTEST_ST_EN ; 
 int /*<<< orphan*/  OMAP_I2C_SYSTEST_TMODE_MASK ; 
 struct omap_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  omap_i2c_read_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_i2c_write_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_i2c_unprepare_recovery(struct i2c_adapter *adap)
{
	struct omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 reg;

	reg = omap_i2c_read_reg(dev, OMAP_I2C_SYSTEST_REG);
	/* restore reset values */
	reg &= ~OMAP_I2C_SYSTEST_ST_EN;
	reg &= ~OMAP_I2C_SYSTEST_TMODE_MASK;
	reg &= ~OMAP_I2C_SYSTEST_SCL_O;
	reg &= ~OMAP_I2C_SYSTEST_SDA_O;
	omap_i2c_write_reg(dev, OMAP_I2C_SYSTEST_REG, reg);
}