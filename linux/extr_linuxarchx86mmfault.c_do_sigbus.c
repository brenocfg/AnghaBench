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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned long cr2; unsigned long error_code; int /*<<< orphan*/  trap_nr; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int BUS_ADRERR ; 
 int /*<<< orphan*/  SIGBUS ; 
 unsigned long X86_PF_USER ; 
 int /*<<< orphan*/  X86_TRAP_PF ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  force_sig_info_fault (int /*<<< orphan*/ ,int,unsigned long,struct task_struct*,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ is_prefetch (struct pt_regs*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  no_context (struct pt_regs*,unsigned long,unsigned long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
do_sigbus(struct pt_regs *regs, unsigned long error_code, unsigned long address,
	  u32 *pkey, unsigned int fault)
{
	struct task_struct *tsk = current;
	int code = BUS_ADRERR;

	/* Kernel mode? Handle exceptions or die: */
	if (!(error_code & X86_PF_USER)) {
		no_context(regs, error_code, address, SIGBUS, BUS_ADRERR);
		return;
	}

	/* User-space => ok to do another page fault: */
	if (is_prefetch(regs, error_code, address))
		return;

	tsk->thread.cr2		= address;
	tsk->thread.error_code	= error_code;
	tsk->thread.trap_nr	= X86_TRAP_PF;

#ifdef CONFIG_MEMORY_FAILURE
	if (fault & (VM_FAULT_HWPOISON|VM_FAULT_HWPOISON_LARGE)) {
		printk(KERN_ERR
	"MCE: Killing %s:%d due to hardware memory corruption fault at %lx\n",
			tsk->comm, tsk->pid, address);
		code = BUS_MCEERR_AR;
	}
#endif
	force_sig_info_fault(SIGBUS, code, address, tsk, pkey, fault);
}