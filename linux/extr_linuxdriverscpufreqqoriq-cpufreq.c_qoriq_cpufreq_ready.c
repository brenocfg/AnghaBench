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
struct cpufreq_policy {struct cpu_data* driver_data; } ;
struct cpu_data {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_cpufreq_cooling_register (struct cpufreq_policy*) ; 

__attribute__((used)) static void qoriq_cpufreq_ready(struct cpufreq_policy *policy)
{
	struct cpu_data *cpud = policy->driver_data;

	cpud->cdev = of_cpufreq_cooling_register(policy);
}