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
struct acpi_processor_performance {int dummy; } ;
struct acpi_cpufreq_data {int /*<<< orphan*/  acpi_perf_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_perf_data ; 
 struct acpi_processor_performance* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct acpi_processor_performance *to_perf_data(struct acpi_cpufreq_data *data)
{
	return per_cpu_ptr(acpi_perf_data, data->acpi_perf_cpu);
}