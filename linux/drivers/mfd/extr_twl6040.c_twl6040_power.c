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
struct twl6040 {scalar_t__ pll; int sysclk_rate; int /*<<< orphan*/  mutex; int /*<<< orphan*/  clk32k; scalar_t__ mclk_rate; int /*<<< orphan*/  mclk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  audpwron; scalar_t__ power_count; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ TWL6040_SYSCLK_SEL_HPPLL ; 
 scalar_t__ TWL6040_SYSCLK_SEL_LPPLL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_power_down_manual (struct twl6040*) ; 
 int twl6040_power_up_automatic (struct twl6040*) ; 
 int twl6040_power_up_manual (struct twl6040*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int twl6040_power(struct twl6040 *twl6040, int on)
{
	int ret = 0;

	mutex_lock(&twl6040->mutex);

	if (on) {
		/* already powered-up */
		if (twl6040->power_count++)
			goto out;

		ret = clk_prepare_enable(twl6040->clk32k);
		if (ret) {
			twl6040->power_count = 0;
			goto out;
		}

		/* Allow writes to the chip */
		regcache_cache_only(twl6040->regmap, false);

		if (gpio_is_valid(twl6040->audpwron)) {
			/* use automatic power-up sequence */
			ret = twl6040_power_up_automatic(twl6040);
			if (ret) {
				clk_disable_unprepare(twl6040->clk32k);
				twl6040->power_count = 0;
				goto out;
			}
		} else {
			/* use manual power-up sequence */
			ret = twl6040_power_up_manual(twl6040);
			if (ret) {
				clk_disable_unprepare(twl6040->clk32k);
				twl6040->power_count = 0;
				goto out;
			}
		}

		/*
		 * Register access can produce errors after power-up unless we
		 * wait at least 8ms based on measurements on duovero.
		 */
		usleep_range(10000, 12000);

		/* Sync with the HW */
		ret = regcache_sync(twl6040->regmap);
		if (ret) {
			dev_err(twl6040->dev, "Failed to sync with the HW: %i\n",
				ret);
			goto out;
		}

		/* Default PLL configuration after power up */
		twl6040->pll = TWL6040_SYSCLK_SEL_LPPLL;
		twl6040->sysclk_rate = 19200000;
	} else {
		/* already powered-down */
		if (!twl6040->power_count) {
			dev_err(twl6040->dev,
				"device is already powered-off\n");
			ret = -EPERM;
			goto out;
		}

		if (--twl6040->power_count)
			goto out;

		if (gpio_is_valid(twl6040->audpwron)) {
			/* use AUDPWRON line */
			gpio_set_value(twl6040->audpwron, 0);

			/* power-down sequence latency */
			usleep_range(500, 700);
		} else {
			/* use manual power-down sequence */
			twl6040_power_down_manual(twl6040);
		}

		/* Set regmap to cache only and mark it as dirty */
		regcache_cache_only(twl6040->regmap, true);
		regcache_mark_dirty(twl6040->regmap);

		twl6040->sysclk_rate = 0;

		if (twl6040->pll == TWL6040_SYSCLK_SEL_HPPLL) {
			clk_disable_unprepare(twl6040->mclk);
			twl6040->mclk_rate = 0;
		}

		clk_disable_unprepare(twl6040->clk32k);
	}

out:
	mutex_unlock(&twl6040->mutex);
	return ret;
}