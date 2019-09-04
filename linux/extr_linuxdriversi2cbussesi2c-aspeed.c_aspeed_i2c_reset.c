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
struct platform_device {int dummy; } ;
struct aspeed_i2c_bus {int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ASPEED_I2C_INTR_CTRL_REG ; 
 scalar_t__ ASPEED_I2C_INTR_STS_REG ; 
 int aspeed_i2c_init (struct aspeed_i2c_bus*,struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int aspeed_i2c_reset(struct aspeed_i2c_bus *bus)
{
	struct platform_device *pdev = to_platform_device(bus->dev);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&bus->lock, flags);

	/* Disable and ack all interrupts. */
	writel(0, bus->base + ASPEED_I2C_INTR_CTRL_REG);
	writel(0xffffffff, bus->base + ASPEED_I2C_INTR_STS_REG);

	ret = aspeed_i2c_init(bus, pdev);

	spin_unlock_irqrestore(&bus->lock, flags);

	return ret;
}