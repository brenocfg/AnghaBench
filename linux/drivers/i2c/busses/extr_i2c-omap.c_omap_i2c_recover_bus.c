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
typedef  int u16 ;
struct omap_i2c_dev {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  OMAP_I2C_SYSTEST_REG ; 
 int OMAP_I2C_SYSTEST_SCL_I_FUNC ; 
 int OMAP_I2C_SYSTEST_SDA_I_FUNC ; 
 int i2c_recover_bus (int /*<<< orphan*/ *) ; 
 int omap_i2c_read_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_i2c_recover_bus(struct omap_i2c_dev *omap)
{
	u16 systest;

	systest = omap_i2c_read_reg(omap, OMAP_I2C_SYSTEST_REG);
	if ((systest & OMAP_I2C_SYSTEST_SCL_I_FUNC) &&
	    (systest & OMAP_I2C_SYSTEST_SDA_I_FUNC))
		return 0; /* bus seems to already be fine */
	if (!(systest & OMAP_I2C_SYSTEST_SCL_I_FUNC))
		return -EBUSY; /* recovery would not fix SCL */
	return i2c_recover_bus(&omap->adapter);
}