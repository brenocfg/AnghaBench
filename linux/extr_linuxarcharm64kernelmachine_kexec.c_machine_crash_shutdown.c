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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crash_save_cpu (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crash_smp_send_stop () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  machine_kexec_mask_interrupts () ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void machine_crash_shutdown(struct pt_regs *regs)
{
	local_irq_disable();

	/* shutdown non-crashing cpus */
	crash_smp_send_stop();

	/* for crashing cpu */
	crash_save_cpu(regs, smp_processor_id());
	machine_kexec_mask_interrupts();

	pr_info("Starting crashdump kernel...\n");
}