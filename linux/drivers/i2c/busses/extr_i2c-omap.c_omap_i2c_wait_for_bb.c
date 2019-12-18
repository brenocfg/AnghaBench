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
struct omap_i2c_dev {int dummy; } ;

/* Variables and functions */
 int OMAP_I2C_STAT_BB ; 
 int /*<<< orphan*/  OMAP_I2C_STAT_REG ; 
 unsigned long OMAP_I2C_TIMEOUT ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int omap_i2c_read_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ) ; 
 int omap_i2c_recover_bus (struct omap_i2c_dev*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int omap_i2c_wait_for_bb(struct omap_i2c_dev *omap)
{
	unsigned long timeout;

	timeout = jiffies + OMAP_I2C_TIMEOUT;
	while (omap_i2c_read_reg(omap, OMAP_I2C_STAT_REG) & OMAP_I2C_STAT_BB) {
		if (time_after(jiffies, timeout))
			return omap_i2c_recover_bus(omap);
		msleep(1);
	}

	return 0;
}