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
 int cpu_logical_map (int) ; 
 scalar_t__ ctrl_base ; 
 int readl_relaxed (scalar_t__) ; 

int hi3xxx_get_cpu_jump(int cpu)
{
	cpu = cpu_logical_map(cpu);
	if (!cpu || !ctrl_base)
		return 0;
	return readl_relaxed(ctrl_base + ((cpu - 1) << 2));
}