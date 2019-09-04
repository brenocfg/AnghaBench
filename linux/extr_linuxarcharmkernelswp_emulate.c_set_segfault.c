#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_6__ {void* si_addr; scalar_t__ si_errno; int /*<<< orphan*/  si_signo; int /*<<< orphan*/  si_code; } ;
typedef  TYPE_1__ siginfo_t ;
struct TYPE_8__ {TYPE_2__* mm; } ;
struct TYPE_7__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEGV_ACCERR ; 
 int /*<<< orphan*/  SEGV_MAPERR ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  abtcounter ; 
 int /*<<< orphan*/  arm_notify_die (char*,struct pt_regs*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_siginfo (TYPE_1__*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_vma (TYPE_2__*,unsigned long) ; 
 scalar_t__ instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_segfault(struct pt_regs *regs, unsigned long addr)
{
	siginfo_t info;

	clear_siginfo(&info);
	down_read(&current->mm->mmap_sem);
	if (find_vma(current->mm, addr) == NULL)
		info.si_code = SEGV_MAPERR;
	else
		info.si_code = SEGV_ACCERR;
	up_read(&current->mm->mmap_sem);

	info.si_signo = SIGSEGV;
	info.si_errno = 0;
	info.si_addr  = (void *) instruction_pointer(regs);

	pr_debug("SWP{B} emulation: access caused memory abort!\n");
	arm_notify_die("Illegal memory access", regs, &info, 0, 0);

	abtcounter++;
}