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
struct rapl_package {int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rapl_package*) ; 
 int PTR_ERR (struct rapl_package*) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 struct rapl_package* rapl_add_package (unsigned int,int /*<<< orphan*/ *) ; 
 struct rapl_package* rapl_find_package_domain (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rapl_msr_priv ; 

__attribute__((used)) static int rapl_cpu_online(unsigned int cpu)
{
	struct rapl_package *rp;

	rp = rapl_find_package_domain(cpu, &rapl_msr_priv);
	if (!rp) {
		rp = rapl_add_package(cpu, &rapl_msr_priv);
		if (IS_ERR(rp))
			return PTR_ERR(rp);
	}
	cpumask_set_cpu(cpu, &rp->cpumask);
	return 0;
}