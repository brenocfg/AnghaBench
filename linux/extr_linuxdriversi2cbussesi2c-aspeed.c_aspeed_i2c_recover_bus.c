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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;
struct aspeed_i2c_bus {int /*<<< orphan*/  lock; scalar_t__ base; scalar_t__ cmd_err; TYPE_1__ adap; int /*<<< orphan*/  cmd_complete; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_I2CD_BUS_RECOVER_CMD ; 
 int /*<<< orphan*/  ASPEED_I2CD_M_STOP_CMD ; 
 int ASPEED_I2CD_SCL_LINE_STS ; 
 int ASPEED_I2CD_SDA_LINE_STS ; 
 scalar_t__ ASPEED_I2C_CMD_REG ; 
 int aspeed_i2c_reset (struct aspeed_i2c_bus*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int aspeed_i2c_recover_bus(struct aspeed_i2c_bus *bus)
{
	unsigned long time_left, flags;
	int ret = 0;
	u32 command;

	spin_lock_irqsave(&bus->lock, flags);
	command = readl(bus->base + ASPEED_I2C_CMD_REG);

	if (command & ASPEED_I2CD_SDA_LINE_STS) {
		/* Bus is idle: no recovery needed. */
		if (command & ASPEED_I2CD_SCL_LINE_STS)
			goto out;
		dev_dbg(bus->dev, "SCL hung (state %x), attempting recovery\n",
			command);

		reinit_completion(&bus->cmd_complete);
		writel(ASPEED_I2CD_M_STOP_CMD, bus->base + ASPEED_I2C_CMD_REG);
		spin_unlock_irqrestore(&bus->lock, flags);

		time_left = wait_for_completion_timeout(
				&bus->cmd_complete, bus->adap.timeout);

		spin_lock_irqsave(&bus->lock, flags);
		if (time_left == 0)
			goto reset_out;
		else if (bus->cmd_err)
			goto reset_out;
		/* Recovery failed. */
		else if (!(readl(bus->base + ASPEED_I2C_CMD_REG) &
			   ASPEED_I2CD_SCL_LINE_STS))
			goto reset_out;
	/* Bus error. */
	} else {
		dev_dbg(bus->dev, "SDA hung (state %x), attempting recovery\n",
			command);

		reinit_completion(&bus->cmd_complete);
		/* Writes 1 to 8 SCL clock cycles until SDA is released. */
		writel(ASPEED_I2CD_BUS_RECOVER_CMD,
		       bus->base + ASPEED_I2C_CMD_REG);
		spin_unlock_irqrestore(&bus->lock, flags);

		time_left = wait_for_completion_timeout(
				&bus->cmd_complete, bus->adap.timeout);

		spin_lock_irqsave(&bus->lock, flags);
		if (time_left == 0)
			goto reset_out;
		else if (bus->cmd_err)
			goto reset_out;
		/* Recovery failed. */
		else if (!(readl(bus->base + ASPEED_I2C_CMD_REG) &
			   ASPEED_I2CD_SDA_LINE_STS))
			goto reset_out;
	}

out:
	spin_unlock_irqrestore(&bus->lock, flags);

	return ret;

reset_out:
	spin_unlock_irqrestore(&bus->lock, flags);

	return aspeed_i2c_reset(bus);
}