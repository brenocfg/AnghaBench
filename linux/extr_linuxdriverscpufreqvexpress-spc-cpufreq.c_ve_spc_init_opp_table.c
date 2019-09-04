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
struct device {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_first (struct cpumask const*) ; 
 scalar_t__ dev_pm_opp_get_opp_count (struct device*) ; 
 struct device* get_cpu_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ve_spc_init_opp_table(const struct cpumask *cpumask)
{
	struct device *cpu_dev = get_cpu_device(cpumask_first(cpumask));
	/*
	 * platform specific SPC code must initialise the opp table
	 * so just check if the OPP count is non-zero
	 */
	return dev_pm_opp_get_opp_count(cpu_dev) <= 0;
}