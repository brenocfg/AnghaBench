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
struct thread_info {int new_child; int flags; struct pt_regs* kregs; int /*<<< orphan*/ * utraps; int /*<<< orphan*/  current_ds; scalar_t__* fpsaved; scalar_t__ ksp; } ;
struct task_struct {int flags; } ;
struct sparc_stackf {int dummy; } ;
struct pt_regs {int tstate; unsigned long* u_regs; } ;
struct TYPE_2__ {unsigned long pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASI_AIUS ; 
 int /*<<< orphan*/  ASI_P ; 
 unsigned long CLONE_SETTLS ; 
 int EFAULT ; 
 int PF_KTHREAD ; 
 unsigned long STACKFRAME_SZ ; 
 scalar_t__ STACK_BIAS ; 
 unsigned long THREAD_SIZE ; 
 size_t TI_FLAG_BYTE_CWP ; 
 unsigned long TRACEREG_SZ ; 
 int TSTATE_CWP ; 
 size_t UREG_FP ; 
 size_t UREG_G1 ; 
 size_t UREG_G2 ; 
 size_t UREG_G7 ; 
 size_t UREG_I0 ; 
 size_t UREG_I1 ; 
 size_t UREG_I3 ; 
 int _TIF_32BIT ; 
 int* __thread_flag_byte_ptr (struct thread_info*) ; 
 unsigned long clone_stackframe (unsigned long,unsigned long) ; 
 TYPE_1__* current ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  memcpy (char*,struct sparc_stackf*,unsigned long) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned long) ; 
 char* task_stack_page (struct task_struct*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

int copy_thread(unsigned long clone_flags, unsigned long sp,
		unsigned long arg, struct task_struct *p)
{
	struct thread_info *t = task_thread_info(p);
	struct pt_regs *regs = current_pt_regs();
	struct sparc_stackf *parent_sf;
	unsigned long child_stack_sz;
	char *child_trap_frame;

	/* Calculate offset to stack_frame & pt_regs */
	child_stack_sz = (STACKFRAME_SZ + TRACEREG_SZ);
	child_trap_frame = (task_stack_page(p) +
			    (THREAD_SIZE - child_stack_sz));

	t->new_child = 1;
	t->ksp = ((unsigned long) child_trap_frame) - STACK_BIAS;
	t->kregs = (struct pt_regs *) (child_trap_frame +
				       sizeof(struct sparc_stackf));
	t->fpsaved[0] = 0;

	if (unlikely(p->flags & PF_KTHREAD)) {
		memset(child_trap_frame, 0, child_stack_sz);
		__thread_flag_byte_ptr(t)[TI_FLAG_BYTE_CWP] = 
			(current_pt_regs()->tstate + 1) & TSTATE_CWP;
		t->current_ds = ASI_P;
		t->kregs->u_regs[UREG_G1] = sp; /* function */
		t->kregs->u_regs[UREG_G2] = arg;
		return 0;
	}

	parent_sf = ((struct sparc_stackf *) regs) - 1;
	memcpy(child_trap_frame, parent_sf, child_stack_sz);
	if (t->flags & _TIF_32BIT) {
		sp &= 0x00000000ffffffffUL;
		regs->u_regs[UREG_FP] &= 0x00000000ffffffffUL;
	}
	t->kregs->u_regs[UREG_FP] = sp;
	__thread_flag_byte_ptr(t)[TI_FLAG_BYTE_CWP] = 
		(regs->tstate + 1) & TSTATE_CWP;
	t->current_ds = ASI_AIUS;
	if (sp != regs->u_regs[UREG_FP]) {
		unsigned long csp;

		csp = clone_stackframe(sp, regs->u_regs[UREG_FP]);
		if (!csp)
			return -EFAULT;
		t->kregs->u_regs[UREG_FP] = csp;
	}
	if (t->utraps)
		t->utraps[0]++;

	/* Set the return value for the child. */
	t->kregs->u_regs[UREG_I0] = current->pid;
	t->kregs->u_regs[UREG_I1] = 1;

	/* Set the second return value for the parent. */
	regs->u_regs[UREG_I1] = 0;

	if (clone_flags & CLONE_SETTLS)
		t->kregs->u_regs[UREG_G7] = regs->u_regs[UREG_I3];

	return 0;
}