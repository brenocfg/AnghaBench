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
struct omap_i2c_dev {scalar_t__ rev; scalar_t__ bb_valid; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int OMAP_I2C_CON_EN ; 
 int /*<<< orphan*/  OMAP_I2C_CON_REG ; 
 scalar_t__ OMAP_I2C_OMAP1_REV_2 ; 
 scalar_t__ OMAP_I2C_REV_ON_3430_3530 ; 
 int /*<<< orphan*/  OMAP_I2C_SYSC_REG ; 
 int /*<<< orphan*/  OMAP_I2C_SYSS_REG ; 
 unsigned long OMAP_I2C_TIMEOUT ; 
 int SYSC_SOFTRESET_MASK ; 
 int SYSS_RESETDONE_MASK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int omap_i2c_read_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_i2c_write_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int omap_i2c_reset(struct omap_i2c_dev *omap)
{
	unsigned long timeout;
	u16 sysc;

	if (omap->rev >= OMAP_I2C_OMAP1_REV_2) {
		sysc = omap_i2c_read_reg(omap, OMAP_I2C_SYSC_REG);

		/* Disable I2C controller before soft reset */
		omap_i2c_write_reg(omap, OMAP_I2C_CON_REG,
			omap_i2c_read_reg(omap, OMAP_I2C_CON_REG) &
				~(OMAP_I2C_CON_EN));

		omap_i2c_write_reg(omap, OMAP_I2C_SYSC_REG, SYSC_SOFTRESET_MASK);
		/* For some reason we need to set the EN bit before the
		 * reset done bit gets set. */
		timeout = jiffies + OMAP_I2C_TIMEOUT;
		omap_i2c_write_reg(omap, OMAP_I2C_CON_REG, OMAP_I2C_CON_EN);
		while (!(omap_i2c_read_reg(omap, OMAP_I2C_SYSS_REG) &
			 SYSS_RESETDONE_MASK)) {
			if (time_after(jiffies, timeout)) {
				dev_warn(omap->dev, "timeout waiting "
						"for controller reset\n");
				return -ETIMEDOUT;
			}
			msleep(1);
		}

		/* SYSC register is cleared by the reset; rewrite it */
		omap_i2c_write_reg(omap, OMAP_I2C_SYSC_REG, sysc);

		if (omap->rev > OMAP_I2C_REV_ON_3430_3530) {
			/* Schedule I2C-bus monitoring on the next transfer */
			omap->bb_valid = 0;
		}
	}

	return 0;
}