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
struct msm_gpu {unsigned long fast_rate; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct dev_pm_opp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int /*<<< orphan*/  IS_ERR (struct dev_pm_opp*) ; 
 unsigned long ULONG_MAX ; 
 int adreno_get_legacy_pwrlevels (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_floor (struct device*,unsigned long*) ; 
 int dev_pm_opp_of_add_table (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adreno_get_pwrlevels(struct device *dev,
		struct msm_gpu *gpu)
{
	unsigned long freq = ULONG_MAX;
	struct dev_pm_opp *opp;
	int ret;

	gpu->fast_rate = 0;

	/* You down with OPP? */
	if (!of_find_property(dev->of_node, "operating-points-v2", NULL))
		ret = adreno_get_legacy_pwrlevels(dev);
	else {
		ret = dev_pm_opp_of_add_table(dev);
		if (ret)
			dev_err(dev, "Unable to set the OPP table\n");
	}

	if (!ret) {
		/* Find the fastest defined rate */
		opp = dev_pm_opp_find_freq_floor(dev, &freq);
		if (!IS_ERR(opp)) {
			gpu->fast_rate = freq;
			dev_pm_opp_put(opp);
		}
	}

	if (!gpu->fast_rate) {
		dev_warn(dev,
			"Could not find a clock rate. Using a reasonable default\n");
		/* Pick a suitably safe clock speed for any target */
		gpu->fast_rate = 200000000;
	}

	DBG("fast_rate=%u, slow_rate=27000000", gpu->fast_rate);

	return 0;
}