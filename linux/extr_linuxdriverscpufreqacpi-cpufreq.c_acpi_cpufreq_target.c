#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpumask {int dummy; } ;
struct cpufreq_policy {scalar_t__ shared_type; unsigned int cpu; TYPE_2__* freq_table; struct cpumask* cpus; struct acpi_cpufreq_data* driver_data; } ;
struct acpi_processor_performance {unsigned int state; TYPE_1__* states; } ;
struct acpi_cpufreq_data {int resume; } ;
struct TYPE_4__ {unsigned int driver_data; int /*<<< orphan*/  frequency; } ;
struct TYPE_3__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 scalar_t__ CPUFREQ_SHARED_TYPE_ANY ; 
 int EAGAIN ; 
 int ENODEV ; 
 scalar_t__ acpi_pstate_strict ; 
 int /*<<< orphan*/  check_freqs (struct cpufreq_policy*,struct cpumask const*,int /*<<< orphan*/ ) ; 
 struct cpumask* cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  drv_write (struct acpi_cpufreq_data*,struct cpumask const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 struct acpi_processor_performance* to_perf_data (struct acpi_cpufreq_data*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int acpi_cpufreq_target(struct cpufreq_policy *policy,
			       unsigned int index)
{
	struct acpi_cpufreq_data *data = policy->driver_data;
	struct acpi_processor_performance *perf;
	const struct cpumask *mask;
	unsigned int next_perf_state = 0; /* Index into perf table */
	int result = 0;

	if (unlikely(!data)) {
		return -ENODEV;
	}

	perf = to_perf_data(data);
	next_perf_state = policy->freq_table[index].driver_data;
	if (perf->state == next_perf_state) {
		if (unlikely(data->resume)) {
			pr_debug("Called after resume, resetting to P%d\n",
				next_perf_state);
			data->resume = 0;
		} else {
			pr_debug("Already at target state (P%d)\n",
				next_perf_state);
			return 0;
		}
	}

	/*
	 * The core won't allow CPUs to go away until the governor has been
	 * stopped, so we can rely on the stability of policy->cpus.
	 */
	mask = policy->shared_type == CPUFREQ_SHARED_TYPE_ANY ?
		cpumask_of(policy->cpu) : policy->cpus;

	drv_write(data, mask, perf->states[next_perf_state].control);

	if (acpi_pstate_strict) {
		if (!check_freqs(policy, mask,
				 policy->freq_table[index].frequency)) {
			pr_debug("acpi_cpufreq_target failed (%d)\n",
				policy->cpu);
			result = -EAGAIN;
		}
	}

	if (!result)
		perf->state = next_perf_state;

	return result;
}