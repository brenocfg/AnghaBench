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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned long cur_freq; unsigned long cur_volt; } ;
struct panfrost_device {TYPE_1__ devfreq; int /*<<< orphan*/  regulator; int /*<<< orphan*/  clock; } ;
struct device {int dummy; } ;
struct dev_pm_opp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int PTR_ERR (struct dev_pm_opp*) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long,...) ; 
 unsigned long dev_pm_opp_get_freq (struct dev_pm_opp*) ; 
 unsigned long dev_pm_opp_get_voltage (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 struct dev_pm_opp* devfreq_recommended_opp (struct device*,unsigned long*,int /*<<< orphan*/ ) ; 
 struct panfrost_device* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 int regulator_set_voltage (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static int panfrost_devfreq_target(struct device *dev, unsigned long *freq,
				   u32 flags)
{
	struct panfrost_device *pfdev = platform_get_drvdata(to_platform_device(dev));
	struct dev_pm_opp *opp;
	unsigned long old_clk_rate = pfdev->devfreq.cur_freq;
	unsigned long target_volt, target_rate;
	int err;

	opp = devfreq_recommended_opp(dev, freq, flags);
	if (IS_ERR(opp))
		return PTR_ERR(opp);

	target_rate = dev_pm_opp_get_freq(opp);
	target_volt = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	if (old_clk_rate == target_rate)
		return 0;

	/*
	 * If frequency scaling from low to high, adjust voltage first.
	 * If frequency scaling from high to low, adjust frequency first.
	 */
	if (old_clk_rate < target_rate) {
		err = regulator_set_voltage(pfdev->regulator, target_volt,
					    target_volt);
		if (err) {
			dev_err(dev, "Cannot set voltage %lu uV\n",
				target_volt);
			return err;
		}
	}

	err = clk_set_rate(pfdev->clock, target_rate);
	if (err) {
		dev_err(dev, "Cannot set frequency %lu (%d)\n", target_rate,
			err);
		regulator_set_voltage(pfdev->regulator, pfdev->devfreq.cur_volt,
				      pfdev->devfreq.cur_volt);
		return err;
	}

	if (old_clk_rate > target_rate) {
		err = regulator_set_voltage(pfdev->regulator, target_volt,
					    target_volt);
		if (err)
			dev_err(dev, "Cannot set voltage %lu uV\n", target_volt);
	}

	pfdev->devfreq.cur_freq = target_rate;
	pfdev->devfreq.cur_volt = target_volt;

	return 0;
}