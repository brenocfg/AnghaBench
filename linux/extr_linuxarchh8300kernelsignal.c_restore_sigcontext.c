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
struct sigcontext {int /*<<< orphan*/  sc_er0; int /*<<< orphan*/  sc_usp; int /*<<< orphan*/  sc_ccr; int /*<<< orphan*/  sc_pc; int /*<<< orphan*/  sc_er5; int /*<<< orphan*/  sc_er3; int /*<<< orphan*/  sc_er2; int /*<<< orphan*/  sc_er1; } ;
struct pt_regs {int er1; int er2; int er3; int er5; int pc; int ccr; int orig_er0; unsigned int sp; } ;
struct TYPE_3__ {int /*<<< orphan*/  fn; } ;
struct TYPE_4__ {TYPE_1__ restart_block; } ;

/* Variables and functions */
 int __get_user (unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  do_no_restart_syscall ; 
 int get_user (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
restore_sigcontext(struct sigcontext *usc, int *pd0)
{
	struct pt_regs *regs = current_pt_regs();
	int err = 0;
	unsigned int ccr;
	unsigned int usp;
	unsigned int er0;

	/* Always make any pending restarted system calls return -EINTR */
	current->restart_block.fn = do_no_restart_syscall;

	/* restore passed registers */
#define COPY(r)  do { err |= get_user(regs->r, &usc->sc_##r); } while (0)
	COPY(er1);
	COPY(er2);
	COPY(er3);
	COPY(er5);
	COPY(pc);
	ccr = regs->ccr & 0x10;
	COPY(ccr);
#undef COPY
	regs->ccr &= 0xef;
	regs->ccr |= ccr;
	regs->orig_er0 = -1;		/* disable syscall checks */
	err |= __get_user(usp, &usc->sc_usp);
	regs->sp = usp;

	err |= __get_user(er0, &usc->sc_er0);
	*pd0 = er0;
	return err;
}