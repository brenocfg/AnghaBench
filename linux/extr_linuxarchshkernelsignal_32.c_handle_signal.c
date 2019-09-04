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
struct pt_regs {int dummy; } ;
struct TYPE_3__ {int sa_flags; } ;
struct TYPE_4__ {TYPE_1__ sa; } ;
struct ksignal {TYPE_2__ ka; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int SA_SIGINFO ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int setup_frame (struct ksignal*,int /*<<< orphan*/ *,struct pt_regs*) ; 
 int setup_rt_frame (struct ksignal*,int /*<<< orphan*/ *,struct pt_regs*) ; 
 int /*<<< orphan*/ * sigmask_to_save () ; 
 int /*<<< orphan*/  signal_setup_done (int,struct ksignal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_signal(struct ksignal *ksig, struct pt_regs *regs, unsigned int save_r0)
{
	sigset_t *oldset = sigmask_to_save();
	int ret;

	/* Set up the stack frame */
	if (ksig->ka.sa.sa_flags & SA_SIGINFO)
		ret = setup_rt_frame(ksig, oldset, regs);
	else
		ret = setup_frame(ksig, oldset, regs);

	signal_setup_done(ret, ksig, test_thread_flag(TIF_SINGLESTEP));
}