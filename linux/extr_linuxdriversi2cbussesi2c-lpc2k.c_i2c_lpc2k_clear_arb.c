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
struct lpc2k_i2c {scalar_t__ base; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ LPC24XX_I2CONSET ; 
 scalar_t__ LPC24XX_I2STAT ; 
 int /*<<< orphan*/  LPC24XX_STO ; 
 scalar_t__ M_I2C_IDLE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  i2c_lpc2k_reset (struct lpc2k_i2c*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ readl (scalar_t__) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int i2c_lpc2k_clear_arb(struct lpc2k_i2c *i2c)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(1000);

	/*
	 * If the transfer needs to abort for some reason, we'll try to
	 * force a stop condition to clear any pending bus conditions
	 */
	writel(LPC24XX_STO, i2c->base + LPC24XX_I2CONSET);

	/* Wait for status change */
	while (readl(i2c->base + LPC24XX_I2STAT) != M_I2C_IDLE) {
		if (time_after(jiffies, timeout)) {
			/* Bus was not idle, try to reset adapter */
			i2c_lpc2k_reset(i2c);
			return -EBUSY;
		}

		cpu_relax();
	}

	return 0;
}