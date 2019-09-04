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
struct s3c2416_data {int is_dvs; int /*<<< orphan*/  hclk; int /*<<< orphan*/  armclk; } ;

/* Variables and functions */
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int s3c2416_cpufreq_enter_dvs(struct s3c2416_data *s3c_freq, int idx)
{
#ifdef CONFIG_ARM_S3C2416_CPUFREQ_VCORESCALE
	struct s3c2416_dvfs *dvfs;
#endif
	int ret;

	if (s3c_freq->is_dvs) {
		pr_debug("cpufreq: already in dvs mode, nothing to do\n");
		return 0;
	}

	pr_debug("cpufreq: switching armclk to hclk (%lukHz)\n",
		 clk_get_rate(s3c_freq->hclk) / 1000);
	ret = clk_set_parent(s3c_freq->armclk, s3c_freq->hclk);
	if (ret < 0) {
		pr_err("cpufreq: Failed to switch armclk to hclk: %d\n", ret);
		return ret;
	}

#ifdef CONFIG_ARM_S3C2416_CPUFREQ_VCORESCALE
	/* changing the core voltage is only allowed when in dvs mode */
	if (s3c_freq->vddarm) {
		dvfs = &s3c2416_dvfs_table[idx];

		pr_debug("cpufreq: setting regulator to %d-%d\n",
			 dvfs->vddarm_min, dvfs->vddarm_max);
		ret = regulator_set_voltage(s3c_freq->vddarm,
					    dvfs->vddarm_min,
					    dvfs->vddarm_max);

		/* when lowering the voltage failed, there is nothing to do */
		if (ret != 0)
			pr_err("cpufreq: Failed to set VDDARM: %d\n", ret);
	}
#endif

	s3c_freq->is_dvs = 1;

	return 0;
}