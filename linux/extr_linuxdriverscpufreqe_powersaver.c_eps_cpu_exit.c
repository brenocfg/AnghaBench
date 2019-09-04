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
struct cpufreq_policy {unsigned int cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** eps_cpu ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eps_cpu_exit(struct cpufreq_policy *policy)
{
	unsigned int cpu = policy->cpu;

	/* Bye */
	kfree(eps_cpu[cpu]);
	eps_cpu[cpu] = NULL;
	return 0;
}