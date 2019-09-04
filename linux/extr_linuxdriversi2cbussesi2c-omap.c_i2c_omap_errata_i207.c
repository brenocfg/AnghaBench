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
struct omap_i2c_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int OMAP_I2C_STAT_BB ; 
 int OMAP_I2C_STAT_RDR ; 
 int /*<<< orphan*/  OMAP_I2C_STAT_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap_i2c_ack_stat (struct omap_i2c_dev*,int) ; 
 int omap_i2c_read_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i2c_omap_errata_i207(struct omap_i2c_dev *omap, u16 stat)
{
	/*
	 * I2C Errata(Errata Nos. OMAP2: 1.67, OMAP3: 1.8)
	 * Not applicable for OMAP4.
	 * Under certain rare conditions, RDR could be set again
	 * when the bus is busy, then ignore the interrupt and
	 * clear the interrupt.
	 */
	if (stat & OMAP_I2C_STAT_RDR) {
		/* Step 1: If RDR is set, clear it */
		omap_i2c_ack_stat(omap, OMAP_I2C_STAT_RDR);

		/* Step 2: */
		if (!(omap_i2c_read_reg(omap, OMAP_I2C_STAT_REG)
						& OMAP_I2C_STAT_BB)) {

			/* Step 3: */
			if (omap_i2c_read_reg(omap, OMAP_I2C_STAT_REG)
						& OMAP_I2C_STAT_RDR) {
				omap_i2c_ack_stat(omap, OMAP_I2C_STAT_RDR);
				dev_dbg(omap->dev, "RDR when bus is busy.\n");
			}

		}
	}
}