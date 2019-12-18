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
 int /*<<< orphan*/  __xen_evtchn_do_upcall () ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  irq_hv_callback_count ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 

void xen_evtchn_do_upcall(struct pt_regs *regs)
{
	struct pt_regs *old_regs = set_irq_regs(regs);

	irq_enter();
#ifdef CONFIG_X86
	inc_irq_stat(irq_hv_callback_count);
#endif

	__xen_evtchn_do_upcall();

	irq_exit();
	set_irq_regs(old_regs);
}