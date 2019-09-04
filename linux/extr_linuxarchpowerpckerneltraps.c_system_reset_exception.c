#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int msr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sreset_irqs; } ;
struct TYPE_3__ {scalar_t__ (* system_reset_exception ) (struct pt_regs*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int MSEC_PER_SEC ; 
 int MSR_RI ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  TAINT_DIE ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crash_fadump (struct pt_regs*,char*) ; 
 int /*<<< orphan*/  crash_kexec (struct pt_regs*) ; 
 int /*<<< orphan*/  crash_kexec_secondary (struct pt_regs*) ; 
 scalar_t__ debugger (struct pt_regs*) ; 
 int /*<<< orphan*/  die (char*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int in_nmi () ; 
 TYPE_2__ irq_stat ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  nmi_enter () ; 
 int /*<<< orphan*/  nmi_exit () ; 
 int /*<<< orphan*/  nmi_panic (struct pt_regs*,char*) ; 
 TYPE_1__ ppc_md ; 
 scalar_t__ stub1 (struct pt_regs*) ; 

void system_reset_exception(struct pt_regs *regs)
{
	/*
	 * Avoid crashes in case of nested NMI exceptions. Recoverability
	 * is determined by RI and in_nmi
	 */
	bool nested = in_nmi();
	if (!nested)
		nmi_enter();

	__this_cpu_inc(irq_stat.sreset_irqs);

	/* See if any machine dependent calls */
	if (ppc_md.system_reset_exception) {
		if (ppc_md.system_reset_exception(regs))
			goto out;
	}

	if (debugger(regs))
		goto out;

	/*
	 * A system reset is a request to dump, so we always send
	 * it through the crashdump code (if fadump or kdump are
	 * registered).
	 */
	crash_fadump(regs, "System Reset");

	crash_kexec(regs);

	/*
	 * We aren't the primary crash CPU. We need to send it
	 * to a holding pattern to avoid it ending up in the panic
	 * code.
	 */
	crash_kexec_secondary(regs);

	/*
	 * No debugger or crash dump registered, print logs then
	 * panic.
	 */
	die("System Reset", regs, SIGABRT);

	mdelay(2*MSEC_PER_SEC); /* Wait a little while for others to print */
	add_taint(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	nmi_panic(regs, "System Reset");

out:
#ifdef CONFIG_PPC_BOOK3S_64
	BUG_ON(get_paca()->in_nmi == 0);
	if (get_paca()->in_nmi > 1)
		nmi_panic(regs, "Unrecoverable nested System Reset");
#endif
	/* Must die if the interrupt is not recoverable */
	if (!(regs->msr & MSR_RI))
		nmi_panic(regs, "Unrecoverable System Reset");

	if (!nested)
		nmi_exit();

	/* What should we do here? We could issue a shutdown or hard reset. */
}