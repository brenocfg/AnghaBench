#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long timeout; } ;
struct davinci_i2c_dev {TYPE_1__ adapter; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DAVINCI_I2C_STR_BB ; 
 int /*<<< orphan*/  DAVINCI_I2C_STR_REG ; 
 int EIO ; 
 int davinci_i2c_read_reg (struct davinci_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i2c_recover_bus (TYPE_1__*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_before_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static int i2c_davinci_wait_bus_not_busy(struct davinci_i2c_dev *dev)
{
	unsigned long timeout = jiffies + dev->adapter.timeout;

	do {
		if (!(davinci_i2c_read_reg(dev, DAVINCI_I2C_STR_REG) & DAVINCI_I2C_STR_BB))
			return 0;
		schedule_timeout_uninterruptible(1);
	} while (time_before_eq(jiffies, timeout));

	dev_warn(dev->dev, "timeout waiting for bus ready\n");
	i2c_recover_bus(&dev->adapter);

	/*
	 * if bus is still "busy" here, it's most probably a HW problem like
	 * short-circuit
	 */
	if (davinci_i2c_read_reg(dev, DAVINCI_I2C_STR_REG) & DAVINCI_I2C_STR_BB)
		return -EIO;

	return 0;
}