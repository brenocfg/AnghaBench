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
 unsigned long cpu_khz_from_cpuid () ; 
 unsigned long cpu_khz_from_msr () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long quick_pit_calibrate () ; 

unsigned long native_calibrate_cpu_early(void)
{
	unsigned long flags, fast_calibrate = cpu_khz_from_cpuid();

	if (!fast_calibrate)
		fast_calibrate = cpu_khz_from_msr();
	if (!fast_calibrate) {
		local_irq_save(flags);
		fast_calibrate = quick_pit_calibrate();
		local_irq_restore(flags);
	}
	return fast_calibrate;
}