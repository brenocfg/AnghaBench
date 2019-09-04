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
struct cpufreq_acpi_req {unsigned int cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  processor_get_freq ; 
 long work_on_cpu (unsigned int,int /*<<< orphan*/ ,struct cpufreq_acpi_req*) ; 

__attribute__((used)) static unsigned int
acpi_cpufreq_get (
	unsigned int		cpu)
{
	struct cpufreq_acpi_req req;
	long ret;

	req.cpu = cpu;
	ret = work_on_cpu(cpu, processor_get_freq, &req);

	return ret > 0 ? (unsigned int) ret : 0;
}