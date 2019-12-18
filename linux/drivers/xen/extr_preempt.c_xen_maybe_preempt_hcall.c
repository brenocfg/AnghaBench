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
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _cond_resched () ; 
 scalar_t__ need_resched () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xen_in_preemptible_hcall ; 

void xen_maybe_preempt_hcall(void)
{
	if (unlikely(__this_cpu_read(xen_in_preemptible_hcall)
		     && need_resched())) {
		/*
		 * Clear flag as we may be rescheduled on a different
		 * cpu.
		 */
		__this_cpu_write(xen_in_preemptible_hcall, false);
		_cond_resched();
		__this_cpu_write(xen_in_preemptible_hcall, true);
	}
}