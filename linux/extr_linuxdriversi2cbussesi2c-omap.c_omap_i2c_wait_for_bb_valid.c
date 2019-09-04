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
struct omap_i2c_dev {int bb_valid; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long OMAP_I2C_BUS_FREE_TIMEOUT ; 
 int OMAP_I2C_STAT_BB ; 
 int OMAP_I2C_STAT_BF ; 
 int /*<<< orphan*/  OMAP_I2C_STAT_REG ; 
 int /*<<< orphan*/  OMAP_I2C_SYSTEST_REG ; 
 int OMAP_I2C_SYSTEST_SCL_I_FUNC ; 
 int OMAP_I2C_SYSTEST_SDA_I_FUNC ; 
 unsigned long OMAP_I2C_TIMEOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int omap_i2c_read_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ) ; 
 int omap_i2c_recover_bus (struct omap_i2c_dev*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int omap_i2c_wait_for_bb_valid(struct omap_i2c_dev *omap)
{
	unsigned long bus_free_timeout = 0;
	unsigned long timeout;
	int bus_free = 0;
	u16 stat, systest;

	if (omap->bb_valid)
		return 0;

	timeout = jiffies + OMAP_I2C_TIMEOUT;
	while (1) {
		stat = omap_i2c_read_reg(omap, OMAP_I2C_STAT_REG);
		/*
		 * We will see BB or BF event in a case IP had detected any
		 * activity on the I2C bus. Now IP correctly tracks the bus
		 * state. BB-bit value is valid.
		 */
		if (stat & (OMAP_I2C_STAT_BB | OMAP_I2C_STAT_BF))
			break;

		/*
		 * Otherwise, we must look signals on the bus to make
		 * the right decision.
		 */
		systest = omap_i2c_read_reg(omap, OMAP_I2C_SYSTEST_REG);
		if ((systest & OMAP_I2C_SYSTEST_SCL_I_FUNC) &&
		    (systest & OMAP_I2C_SYSTEST_SDA_I_FUNC)) {
			if (!bus_free) {
				bus_free_timeout = jiffies +
					OMAP_I2C_BUS_FREE_TIMEOUT;
				bus_free = 1;
			}

			/*
			 * SDA and SCL lines was high for 10 ms without bus
			 * activity detected. The bus is free. Consider
			 * BB-bit value is valid.
			 */
			if (time_after(jiffies, bus_free_timeout))
				break;
		} else {
			bus_free = 0;
		}

		if (time_after(jiffies, timeout)) {
			/*
			 * SDA or SCL were low for the entire timeout without
			 * any activity detected. Most likely, a slave is
			 * locking up the bus with no master driving the clock.
			 */
			dev_warn(omap->dev, "timeout waiting for bus ready\n");
			return omap_i2c_recover_bus(omap);
		}

		msleep(1);
	}

	omap->bb_valid = 1;
	return 0;
}