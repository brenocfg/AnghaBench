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
 int PWR_EVENT_EXIT ; 
 scalar_t__ omap_irq_pending () ; 
 int /*<<< orphan*/  omap_sram_idle () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  trace_cpu_idle_rcuidle (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap3_pm_idle(void)
{
	if (omap_irq_pending())
		return;

	trace_cpu_idle_rcuidle(1, smp_processor_id());

	omap_sram_idle();

	trace_cpu_idle_rcuidle(PWR_EVENT_EXIT, smp_processor_id());
}