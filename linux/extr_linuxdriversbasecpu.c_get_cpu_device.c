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

/* Variables and functions */
 scalar_t__ cpu_possible (unsigned int) ; 
 int /*<<< orphan*/  cpu_sys_devices ; 
 unsigned int nr_cpu_ids ; 
 struct device* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

struct device *get_cpu_device(unsigned cpu)
{
	if (cpu < nr_cpu_ids && cpu_possible(cpu))
		return per_cpu(cpu_sys_devices, cpu);
	else
		return NULL;
}