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
struct dw_i2c_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_IC_ENABLE_STATUS ; 
 int /*<<< orphan*/  __i2c_dw_disable_nowait (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int dw_readl (struct dw_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void __i2c_dw_disable(struct dw_i2c_dev *dev)
{
	int timeout = 100;

	do {
		__i2c_dw_disable_nowait(dev);
		/*
		 * The enable status register may be unimplemented, but
		 * in that case this test reads zero and exits the loop.
		 */
		if ((dw_readl(dev, DW_IC_ENABLE_STATUS) & 1) == 0)
			return;

		/*
		 * Wait 10 times the signaling period of the highest I2C
		 * transfer supported by the driver (for 400KHz this is
		 * 25us) as described in the DesignWare I2C databook.
		 */
		usleep_range(25, 250);
	} while (timeout--);

	dev_warn(dev->dev, "timeout in disabling adapter\n");
}