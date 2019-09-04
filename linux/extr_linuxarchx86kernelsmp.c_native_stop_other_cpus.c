#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI_allbutself ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NMI_FLAG_FIRST ; 
 int /*<<< orphan*/  NMI_LOCAL ; 
 int /*<<< orphan*/  NMI_VECTOR ; 
 int /*<<< orphan*/  REBOOT_VECTOR ; 
 int USEC_PER_MSEC ; 
 unsigned long USEC_PER_SEC ; 
 TYPE_1__* apic ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_info ; 
 int /*<<< orphan*/  disable_local_APIC () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mcheck_cpu_clear (int /*<<< orphan*/ ) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 scalar_t__ reboot_force ; 
 scalar_t__ register_nmi_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  safe_smp_processor_id () ; 
 int /*<<< orphan*/  smp_no_nmi_ipi ; 
 int /*<<< orphan*/  smp_stop_nmi_callback ; 
 int /*<<< orphan*/  stopping_cpu ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void native_stop_other_cpus(int wait)
{
	unsigned long flags;
	unsigned long timeout;

	if (reboot_force)
		return;

	/*
	 * Use an own vector here because smp_call_function
	 * does lots of things not suitable in a panic situation.
	 */

	/*
	 * We start by using the REBOOT_VECTOR irq.
	 * The irq is treated as a sync point to allow critical
	 * regions of code on other cpus to release their spin locks
	 * and re-enable irqs.  Jumping straight to an NMI might
	 * accidentally cause deadlocks with further shutdown/panic
	 * code.  By syncing, we give the cpus up to one second to
	 * finish their work before we force them off with the NMI.
	 */
	if (num_online_cpus() > 1) {
		/* did someone beat us here? */
		if (atomic_cmpxchg(&stopping_cpu, -1, safe_smp_processor_id()) != -1)
			return;

		/* sync above data before sending IRQ */
		wmb();

		apic->send_IPI_allbutself(REBOOT_VECTOR);

		/*
		 * Don't wait longer than a second if the caller
		 * didn't ask us to wait.
		 */
		timeout = USEC_PER_SEC;
		while (num_online_cpus() > 1 && (wait || timeout--))
			udelay(1);
	}
	
	/* if the REBOOT_VECTOR didn't work, try with the NMI */
	if ((num_online_cpus() > 1) && (!smp_no_nmi_ipi))  {
		if (register_nmi_handler(NMI_LOCAL, smp_stop_nmi_callback,
					 NMI_FLAG_FIRST, "smp_stop"))
			/* Note: we ignore failures here */
			/* Hope the REBOOT_IRQ is good enough */
			goto finish;

		/* sync above data before sending IRQ */
		wmb();

		pr_emerg("Shutting down cpus with NMI\n");

		apic->send_IPI_allbutself(NMI_VECTOR);

		/*
		 * Don't wait longer than a 10 ms if the caller
		 * didn't ask us to wait.
		 */
		timeout = USEC_PER_MSEC * 10;
		while (num_online_cpus() > 1 && (wait || timeout--))
			udelay(1);
	}

finish:
	local_irq_save(flags);
	disable_local_APIC();
	mcheck_cpu_clear(this_cpu_ptr(&cpu_info));
	local_irq_restore(flags);
}