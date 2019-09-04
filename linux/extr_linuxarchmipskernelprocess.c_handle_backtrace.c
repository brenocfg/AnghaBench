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
 int /*<<< orphan*/  backtrace_csd_busy ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 int /*<<< orphan*/  nmi_cpu_backtrace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void handle_backtrace(void *info)
{
	nmi_cpu_backtrace(get_irq_regs());
	cpumask_clear_cpu(smp_processor_id(), &backtrace_csd_busy);
}