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
struct aspeed_i2c_bus {int /*<<< orphan*/  adap; int /*<<< orphan*/  rst; int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ASPEED_I2C_FUN_CTRL_REG ; 
 scalar_t__ ASPEED_I2C_INTR_CTRL_REG ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct aspeed_i2c_bus* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int aspeed_i2c_remove_bus(struct platform_device *pdev)
{
	struct aspeed_i2c_bus *bus = platform_get_drvdata(pdev);
	unsigned long flags;

	spin_lock_irqsave(&bus->lock, flags);

	/* Disable everything. */
	writel(0, bus->base + ASPEED_I2C_FUN_CTRL_REG);
	writel(0, bus->base + ASPEED_I2C_INTR_CTRL_REG);

	spin_unlock_irqrestore(&bus->lock, flags);

	reset_control_assert(bus->rst);

	i2c_del_adapter(&bus->adap);

	return 0;
}