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
struct cpufreq_policy {struct acpi_cpufreq_data* driver_data; } ;
struct acpi_cpufreq_data {int /*<<< orphan*/  freqdomain_cpus; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  cpufreq_show_cpus (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t show_freqdomain_cpus(struct cpufreq_policy *policy, char *buf)
{
	struct acpi_cpufreq_data *data = policy->driver_data;

	if (unlikely(!data))
		return -ENODEV;

	return cpufreq_show_cpus(data->freqdomain_cpus, buf);
}