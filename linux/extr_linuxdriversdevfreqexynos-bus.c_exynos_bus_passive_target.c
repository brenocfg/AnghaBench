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
typedef  int /*<<< orphan*/  u32 ;
struct exynos_bus {unsigned long curr_freq; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; } ;
struct device {int dummy; } ;
struct dev_pm_opp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int PTR_ERR (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct exynos_bus* dev_get_drvdata (struct device*) ; 
 unsigned long dev_pm_opp_get_freq (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 struct dev_pm_opp* devfreq_recommended_opp (struct device*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exynos_bus_passive_target(struct device *dev, unsigned long *freq,
					u32 flags)
{
	struct exynos_bus *bus = dev_get_drvdata(dev);
	struct dev_pm_opp *new_opp;
	unsigned long old_freq, new_freq;
	int ret = 0;

	/* Get new opp-bus instance according to new bus clock */
	new_opp = devfreq_recommended_opp(dev, freq, flags);
	if (IS_ERR(new_opp)) {
		dev_err(dev, "failed to get recommended opp instance\n");
		return PTR_ERR(new_opp);
	}

	new_freq = dev_pm_opp_get_freq(new_opp);
	dev_pm_opp_put(new_opp);

	old_freq = bus->curr_freq;

	if (old_freq == new_freq)
		return 0;

	/* Change the frequency according to new OPP level */
	mutex_lock(&bus->lock);

	ret = clk_set_rate(bus->clk, new_freq);
	if (ret < 0) {
		dev_err(dev, "failed to set the clock of bus\n");
		goto out;
	}

	*freq = new_freq;
	bus->curr_freq = new_freq;

	dev_dbg(dev, "Set the frequency of bus (%luHz -> %luHz, %luHz)\n",
			old_freq, new_freq, clk_get_rate(bus->clk));
out:
	mutex_unlock(&bus->lock);

	return ret;
}