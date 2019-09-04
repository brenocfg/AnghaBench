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

/* Variables and functions */
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_cpu_init_mask ; 

__attribute__((used)) static void tegra_secondary_init(unsigned int cpu)
{
	cpumask_set_cpu(cpu, &tegra_cpu_init_mask);
}