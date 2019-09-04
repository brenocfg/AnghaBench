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
struct pxa_freqs {unsigned int khz; } ;
struct pxa_cpufreq_data {int /*<<< orphan*/  clk_core; } ;
struct cpufreq_policy {int cur; } ;
struct cpufreq_frequency_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 struct pxa_cpufreq_data* cpufreq_get_driver_data () ; 
 int /*<<< orphan*/  find_freq_tables (struct cpufreq_frequency_table**,struct pxa_freqs const**) ; 
 scalar_t__ freq_debug ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned int) ; 
 int pxa_cpufreq_change_voltage (struct pxa_freqs const*) ; 
 scalar_t__ vcc_core ; 

__attribute__((used)) static int pxa_set_target(struct cpufreq_policy *policy, unsigned int idx)
{
	struct cpufreq_frequency_table *pxa_freqs_table;
	const struct pxa_freqs *pxa_freq_settings;
	struct pxa_cpufreq_data *data = cpufreq_get_driver_data();
	unsigned int new_freq_cpu;
	int ret = 0;

	/* Get the current policy */
	find_freq_tables(&pxa_freqs_table, &pxa_freq_settings);

	new_freq_cpu = pxa_freq_settings[idx].khz;

	if (freq_debug)
		pr_debug("Changing CPU frequency from %d Mhz to %d Mhz\n",
			 policy->cur / 1000,  new_freq_cpu / 1000);

	if (vcc_core && new_freq_cpu > policy->cur) {
		ret = pxa_cpufreq_change_voltage(&pxa_freq_settings[idx]);
		if (ret)
			return ret;
	}

	clk_set_rate(data->clk_core, new_freq_cpu * 1000);

	/*
	 * Even if voltage setting fails, we don't report it, as the frequency
	 * change succeeded. The voltage reduction is not a critical failure,
	 * only power savings will suffer from this.
	 *
	 * Note: if the voltage change fails, and a return value is returned, a
	 * bug is triggered (seems a deadlock). Should anybody find out where,
	 * the "return 0" should become a "return ret".
	 */
	if (vcc_core && new_freq_cpu < policy->cur)
		ret = pxa_cpufreq_change_voltage(&pxa_freq_settings[idx]);

	return 0;
}