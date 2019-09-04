#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* xstate; } ;
struct task_struct {TYPE_1__ thread; } ;
struct sh_fpu_soft_struct {void* fpscr; } ;
struct sh_fpu_hard_struct {void* fpscr; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {struct sh_fpu_soft_struct softfpu; struct sh_fpu_soft_struct hardfpu; } ;

/* Variables and functions */
 int CPU_HAS_FPU ; 
 int ENOMEM ; 
 void* FPSCR_INIT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__ boot_cpu_data ; 
 struct task_struct* current ; 
 TYPE_2__* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sh_fpu_soft_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_stopped_child_used_math (struct task_struct*) ; 
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 
 int /*<<< orphan*/  task_xstate_cachep ; 
 scalar_t__ tsk_used_math (struct task_struct*) ; 
 int /*<<< orphan*/  unlazy_fpu (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstate_size ; 

int init_fpu(struct task_struct *tsk)
{
	if (tsk_used_math(tsk)) {
		if ((boot_cpu_data.flags & CPU_HAS_FPU) && tsk == current)
			unlazy_fpu(tsk, task_pt_regs(tsk));
		return 0;
	}

	/*
	 * Memory allocation at the first usage of the FPU and other state.
	 */
	if (!tsk->thread.xstate) {
		tsk->thread.xstate = kmem_cache_alloc(task_xstate_cachep,
						      GFP_KERNEL);
		if (!tsk->thread.xstate)
			return -ENOMEM;
	}

	if (boot_cpu_data.flags & CPU_HAS_FPU) {
		struct sh_fpu_hard_struct *fp = &tsk->thread.xstate->hardfpu;
		memset(fp, 0, xstate_size);
		fp->fpscr = FPSCR_INIT;
	} else {
		struct sh_fpu_soft_struct *fp = &tsk->thread.xstate->softfpu;
		memset(fp, 0, xstate_size);
		fp->fpscr = FPSCR_INIT;
	}

	set_stopped_child_used_math(tsk);
	return 0;
}