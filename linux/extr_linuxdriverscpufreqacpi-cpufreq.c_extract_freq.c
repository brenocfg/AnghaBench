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
struct cpufreq_policy {struct acpi_cpufreq_data* driver_data; } ;
struct acpi_cpufreq_data {int cpu_feature; } ;

/* Variables and functions */
#define  SYSTEM_AMD_MSR_CAPABLE 130 
#define  SYSTEM_INTEL_MSR_CAPABLE 129 
#define  SYSTEM_IO_CAPABLE 128 
 int extract_io (struct cpufreq_policy*,int /*<<< orphan*/ ) ; 
 int extract_msr (struct cpufreq_policy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned extract_freq(struct cpufreq_policy *policy, u32 val)
{
	struct acpi_cpufreq_data *data = policy->driver_data;

	switch (data->cpu_feature) {
	case SYSTEM_INTEL_MSR_CAPABLE:
	case SYSTEM_AMD_MSR_CAPABLE:
		return extract_msr(policy, val);
	case SYSTEM_IO_CAPABLE:
		return extract_io(policy, val);
	default:
		return 0;
	}
}