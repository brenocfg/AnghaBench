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
struct pt_regs {unsigned long nip; int /*<<< orphan*/  msr; } ;
struct kprobe_ctlblk {int kprobe_status; int /*<<< orphan*/  kprobe_saved_msr; } ;
struct kprobe {int /*<<< orphan*/  (* fault_handler ) (struct kprobe*,struct pt_regs*,int) ;scalar_t__ addr; } ;
struct exception_table_entry {int dummy; } ;

/* Variables and functions */
#define  KPROBE_HIT_ACTIVE 131 
#define  KPROBE_HIT_SS 130 
#define  KPROBE_HIT_SSDONE 129 
#define  KPROBE_REENTER 128 
 int /*<<< orphan*/  MSR_SINGLESTEP ; 
 unsigned long extable_fixup (struct exception_table_entry const*) ; 
 struct kprobe_ctlblk* get_kprobe_ctlblk () ; 
 struct kprobe* kprobe_running () ; 
 int /*<<< orphan*/  kprobes_inc_nmissed_count (struct kprobe*) ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  reset_current_kprobe () ; 
 int /*<<< orphan*/  restore_previous_kprobe (struct kprobe_ctlblk*) ; 
 struct exception_table_entry* search_exception_tables (unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct kprobe*,struct pt_regs*,int) ; 

int kprobe_fault_handler(struct pt_regs *regs, int trapnr)
{
	struct kprobe *cur = kprobe_running();
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	const struct exception_table_entry *entry;

	switch(kcb->kprobe_status) {
	case KPROBE_HIT_SS:
	case KPROBE_REENTER:
		/*
		 * We are here because the instruction being single
		 * stepped caused a page fault. We reset the current
		 * kprobe and the nip points back to the probe address
		 * and allow the page fault handler to continue as a
		 * normal page fault.
		 */
		regs->nip = (unsigned long)cur->addr;
		regs->msr &= ~MSR_SINGLESTEP; /* Turn off 'trace' bits */
		regs->msr |= kcb->kprobe_saved_msr;
		if (kcb->kprobe_status == KPROBE_REENTER)
			restore_previous_kprobe(kcb);
		else
			reset_current_kprobe();
		preempt_enable_no_resched();
		break;
	case KPROBE_HIT_ACTIVE:
	case KPROBE_HIT_SSDONE:
		/*
		 * We increment the nmissed count for accounting,
		 * we can also use npre/npostfault count for accounting
		 * these specific fault cases.
		 */
		kprobes_inc_nmissed_count(cur);

		/*
		 * We come here because instructions in the pre/post
		 * handler caused the page_fault, this could happen
		 * if handler tries to access user space by
		 * copy_from_user(), get_user() etc. Let the
		 * user-specified handler try to fix it first.
		 */
		if (cur->fault_handler && cur->fault_handler(cur, regs, trapnr))
			return 1;

		/*
		 * In case the user-specified fault handler returned
		 * zero, try to fix up.
		 */
		if ((entry = search_exception_tables(regs->nip)) != NULL) {
			regs->nip = extable_fixup(entry);
			return 1;
		}

		/*
		 * fixup_exception() could not handle it,
		 * Let do_page_fault() fix it.
		 */
		break;
	default:
		break;
	}
	return 0;
}