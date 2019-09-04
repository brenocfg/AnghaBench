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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int cpu_logical_map (unsigned int) ; 
 int rcar_sysc_power_up_cpu (unsigned int) ; 

__attribute__((used)) static int r8a7779_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	int ret = -EIO;

	cpu = cpu_logical_map(cpu);
	if (cpu)
		ret = rcar_sysc_power_up_cpu(cpu);

	return ret;
}