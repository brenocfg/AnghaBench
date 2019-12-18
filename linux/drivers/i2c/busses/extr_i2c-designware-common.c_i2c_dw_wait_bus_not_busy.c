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
struct dw_i2c_dev {int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_IC_STATUS ; 
 int DW_IC_STATUS_ACTIVITY ; 
 int ETIMEDOUT ; 
 int TIMEOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int dw_readl (struct dw_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_recover_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int i2c_dw_wait_bus_not_busy(struct dw_i2c_dev *dev)
{
	int timeout = TIMEOUT;

	while (dw_readl(dev, DW_IC_STATUS) & DW_IC_STATUS_ACTIVITY) {
		if (timeout <= 0) {
			dev_warn(dev->dev, "timeout waiting for bus ready\n");
			i2c_recover_bus(&dev->adapter);

			if (dw_readl(dev, DW_IC_STATUS) & DW_IC_STATUS_ACTIVITY)
				return -ETIMEDOUT;
			return 0;
		}
		timeout--;
		usleep_range(1000, 1100);
	}

	return 0;
}