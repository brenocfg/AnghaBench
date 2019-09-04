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
struct thread_info {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {unsigned long ksp; int /*<<< orphan*/ * fp_save_area; struct pt_regs* regs; } ;
struct task_struct {int flags; TYPE_1__ thread; } ;
struct pt_regs {unsigned long* gpr; int msr; void* nip; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FULL_REGS (struct pt_regs*) ; 
 unsigned long CLONE_SETTLS ; 
 int MSR_FP ; 
 int MSR_VEC ; 
 int MSR_VSX ; 
 int PF_KTHREAD ; 
 scalar_t__ STACK_FRAME_OVERHEAD ; 
 unsigned long THREAD_SIZE ; 
 int /*<<< orphan*/  _TIF_RESTOREALL ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  klp_init_thread_info (struct thread_info*) ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 void* ppc_function_entry (void (*) ()) ; 
 int /*<<< orphan*/  setup_ksp_vsid (struct task_struct*,unsigned long) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

int copy_thread(unsigned long clone_flags, unsigned long usp,
		unsigned long kthread_arg, struct task_struct *p)
{
	struct pt_regs *childregs, *kregs;
	extern void ret_from_fork(void);
	extern void ret_from_kernel_thread(void);
	void (*f)(void);
	unsigned long sp = (unsigned long)task_stack_page(p) + THREAD_SIZE;
	struct thread_info *ti = task_thread_info(p);

	klp_init_thread_info(ti);

	/* Copy registers */
	sp -= sizeof(struct pt_regs);
	childregs = (struct pt_regs *) sp;
	if (unlikely(p->flags & PF_KTHREAD)) {
		/* kernel thread */
		memset(childregs, 0, sizeof(struct pt_regs));
		childregs->gpr[1] = sp + sizeof(struct pt_regs);
		/* function */
		if (usp)
			childregs->gpr[14] = ppc_function_entry((void *)usp);
#ifdef CONFIG_PPC64
		clear_tsk_thread_flag(p, TIF_32BIT);
		childregs->softe = IRQS_ENABLED;
#endif
		childregs->gpr[15] = kthread_arg;
		p->thread.regs = NULL;	/* no user register state */
		ti->flags |= _TIF_RESTOREALL;
		f = ret_from_kernel_thread;
	} else {
		/* user thread */
		struct pt_regs *regs = current_pt_regs();
		CHECK_FULL_REGS(regs);
		*childregs = *regs;
		if (usp)
			childregs->gpr[1] = usp;
		p->thread.regs = childregs;
		childregs->gpr[3] = 0;  /* Result from fork() */
		if (clone_flags & CLONE_SETTLS) {
#ifdef CONFIG_PPC64
			if (!is_32bit_task())
				childregs->gpr[13] = childregs->gpr[6];
			else
#endif
				childregs->gpr[2] = childregs->gpr[6];
		}

		f = ret_from_fork;
	}
	childregs->msr &= ~(MSR_FP|MSR_VEC|MSR_VSX);
	sp -= STACK_FRAME_OVERHEAD;

	/*
	 * The way this works is that at some point in the future
	 * some task will call _switch to switch to the new task.
	 * That will pop off the stack frame created below and start
	 * the new task running at ret_from_fork.  The new task will
	 * do some house keeping and then return from the fork or clone
	 * system call, using the stack frame created above.
	 */
	((unsigned long *)sp)[0] = 0;
	sp -= sizeof(struct pt_regs);
	kregs = (struct pt_regs *) sp;
	sp -= STACK_FRAME_OVERHEAD;
	p->thread.ksp = sp;
#ifdef CONFIG_PPC32
	p->thread.ksp_limit = (unsigned long)task_stack_page(p) +
				_ALIGN_UP(sizeof(struct thread_info), 16);
#endif
#ifdef CONFIG_HAVE_HW_BREAKPOINT
	p->thread.ptrace_bps[0] = NULL;
#endif

	p->thread.fp_save_area = NULL;
#ifdef CONFIG_ALTIVEC
	p->thread.vr_save_area = NULL;
#endif

	setup_ksp_vsid(p, sp);

#ifdef CONFIG_PPC64 
	if (cpu_has_feature(CPU_FTR_DSCR)) {
		p->thread.dscr_inherit = current->thread.dscr_inherit;
		p->thread.dscr = mfspr(SPRN_DSCR);
	}
	if (cpu_has_feature(CPU_FTR_HAS_PPR))
		p->thread.ppr = INIT_PPR;

	p->thread.tidr = 0;
#endif
	kregs->nip = ppc_function_entry(f);
	return 0;
}