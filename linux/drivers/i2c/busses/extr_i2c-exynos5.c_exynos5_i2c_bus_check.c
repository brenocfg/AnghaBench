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
struct exynos5_i2c {scalar_t__ regs; TYPE_1__* variant; } ;
struct TYPE_2__ {scalar_t__ hw; } ;

/* Variables and functions */
 int HSI2C_MASTER_ST_LOSE ; 
 int HSI2C_MASTER_ST_MASK ; 
 scalar_t__ HSI2C_TRANS_STATUS ; 
 scalar_t__ I2C_TYPE_EXYNOS7 ; 
 int /*<<< orphan*/  exynos5_i2c_bus_recover (struct exynos5_i2c*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_is_before_jiffies (unsigned long) ; 

__attribute__((used)) static void exynos5_i2c_bus_check(struct exynos5_i2c *i2c)
{
	unsigned long timeout;

	if (i2c->variant->hw != I2C_TYPE_EXYNOS7)
		return;

	/*
	 * HSI2C_MASTER_ST_LOSE state in EXYNOS7 variant before transaction
	 * indicates that bus is stuck (SDA is low). In such case bus recovery
	 * can be performed.
	 */
	timeout = jiffies + msecs_to_jiffies(100);
	for (;;) {
		u32 st = readl(i2c->regs + HSI2C_TRANS_STATUS);

		if ((st & HSI2C_MASTER_ST_MASK) != HSI2C_MASTER_ST_LOSE)
			return;

		if (time_is_before_jiffies(timeout))
			return;

		exynos5_i2c_bus_recover(i2c);
	}
}