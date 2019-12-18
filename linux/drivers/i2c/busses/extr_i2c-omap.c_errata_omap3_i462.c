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
struct omap_i2c_dev {int cmd_err; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int OMAP_I2C_STAT_AL ; 
 int OMAP_I2C_STAT_NACK ; 
 int /*<<< orphan*/  OMAP_I2C_STAT_REG ; 
 int OMAP_I2C_STAT_XDR ; 
 int OMAP_I2C_STAT_XRDY ; 
 int OMAP_I2C_STAT_XUDF ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap_i2c_ack_stat (struct omap_i2c_dev*,int) ; 
 int omap_i2c_read_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int errata_omap3_i462(struct omap_i2c_dev *omap)
{
	unsigned long timeout = 10000;
	u16 stat;

	do {
		stat = omap_i2c_read_reg(omap, OMAP_I2C_STAT_REG);
		if (stat & OMAP_I2C_STAT_XUDF)
			break;

		if (stat & (OMAP_I2C_STAT_NACK | OMAP_I2C_STAT_AL)) {
			omap_i2c_ack_stat(omap, (OMAP_I2C_STAT_XRDY |
							OMAP_I2C_STAT_XDR));
			if (stat & OMAP_I2C_STAT_NACK) {
				omap->cmd_err |= OMAP_I2C_STAT_NACK;
				omap_i2c_ack_stat(omap, OMAP_I2C_STAT_NACK);
			}

			if (stat & OMAP_I2C_STAT_AL) {
				dev_err(omap->dev, "Arbitration lost\n");
				omap->cmd_err |= OMAP_I2C_STAT_AL;
				omap_i2c_ack_stat(omap, OMAP_I2C_STAT_AL);
			}

			return -EIO;
		}

		cpu_relax();
	} while (--timeout);

	if (!timeout) {
		dev_err(omap->dev, "timeout waiting on XUDF bit\n");
		return 0;
	}

	return 0;
}