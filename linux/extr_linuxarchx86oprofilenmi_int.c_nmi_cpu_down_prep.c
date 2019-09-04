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
 scalar_t__ ctr_running ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  nmi_cpu_shutdown () ; 
 int /*<<< orphan*/  nmi_cpu_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ nmi_enabled ; 

__attribute__((used)) static int nmi_cpu_down_prep(unsigned int cpu)
{
	local_irq_disable();
	if (ctr_running)
		nmi_cpu_stop(NULL);
	if (nmi_enabled)
		nmi_cpu_shutdown();
	local_irq_enable();
	return 0;
}