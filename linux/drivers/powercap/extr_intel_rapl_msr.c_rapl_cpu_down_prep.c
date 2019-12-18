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
struct rapl_package {unsigned int lead_cpu; int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int cpumask_first (int /*<<< orphan*/ *) ; 
 int nr_cpu_ids ; 
 struct rapl_package* rapl_find_package_domain (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rapl_msr_priv ; 
 int /*<<< orphan*/  rapl_remove_package (struct rapl_package*) ; 

__attribute__((used)) static int rapl_cpu_down_prep(unsigned int cpu)
{
	struct rapl_package *rp;
	int lead_cpu;

	rp = rapl_find_package_domain(cpu, &rapl_msr_priv);
	if (!rp)
		return 0;

	cpumask_clear_cpu(cpu, &rp->cpumask);
	lead_cpu = cpumask_first(&rp->cpumask);
	if (lead_cpu >= nr_cpu_ids)
		rapl_remove_package(rp);
	else if (rp->lead_cpu == cpu)
		rp->lead_cpu = lead_cpu;
	return 0;
}