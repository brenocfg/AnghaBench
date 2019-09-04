#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rt_sigframe_user_layout {TYPE_1__* next_frame; scalar_t__ sigframe; } ;
struct pt_regs {int* regs; unsigned long sp; unsigned long pc; } ;
struct TYPE_7__ {int sa_flags; scalar_t__ sa_restorer; scalar_t__ sa_handler; } ;
struct k_sigaction {TYPE_2__ sa; } ;
typedef  scalar_t__ __sigrestore_t ;
struct TYPE_10__ {TYPE_4__* mm; } ;
struct TYPE_8__ {int /*<<< orphan*/  vdso; } ;
struct TYPE_9__ {TYPE_3__ context; } ;
struct TYPE_6__ {int /*<<< orphan*/  fp; } ;

/* Variables and functions */
 int SA_RESTORER ; 
 scalar_t__ VDSO_SYMBOL (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* current ; 

__attribute__((used)) static void setup_return(struct pt_regs *regs, struct k_sigaction *ka,
			 struct rt_sigframe_user_layout *user, int usig)
{
	__sigrestore_t sigtramp;

	regs->regs[0] = usig;
	regs->sp = (unsigned long)user->sigframe;
	regs->regs[29] = (unsigned long)&user->next_frame->fp;
	regs->pc = (unsigned long)ka->sa.sa_handler;

	if (ka->sa.sa_flags & SA_RESTORER)
		sigtramp = ka->sa.sa_restorer;
	else
		sigtramp = VDSO_SYMBOL(current->mm->context.vdso, sigtramp);

	regs->regs[30] = (unsigned long)sigtramp;
}