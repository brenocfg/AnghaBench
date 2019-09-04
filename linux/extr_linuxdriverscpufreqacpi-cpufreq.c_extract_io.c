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
typedef  scalar_t__ u32 ;
struct cpufreq_policy {TYPE_2__* freq_table; struct acpi_cpufreq_data* driver_data; } ;
struct acpi_processor_performance {int state_count; TYPE_1__* states; } ;
struct acpi_cpufreq_data {int dummy; } ;
struct TYPE_4__ {int frequency; } ;
struct TYPE_3__ {scalar_t__ status; } ;

/* Variables and functions */
 struct acpi_processor_performance* to_perf_data (struct acpi_cpufreq_data*) ; 

__attribute__((used)) static unsigned extract_io(struct cpufreq_policy *policy, u32 value)
{
	struct acpi_cpufreq_data *data = policy->driver_data;
	struct acpi_processor_performance *perf;
	int i;

	perf = to_perf_data(data);

	for (i = 0; i < perf->state_count; i++) {
		if (value == perf->states[i].status)
			return policy->freq_table[i].frequency;
	}
	return 0;
}