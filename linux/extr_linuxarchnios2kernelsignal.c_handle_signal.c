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
struct ksignal {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int setup_rt_frame (struct ksignal*,int /*<<< orphan*/ *,struct pt_regs*) ; 
 int /*<<< orphan*/ * sigmask_to_save () ; 
 int /*<<< orphan*/  signal_setup_done (int,struct ksignal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_signal(struct ksignal *ksig, struct pt_regs *regs)
{
	int ret;
	sigset_t *oldset = sigmask_to_save();

	/* set up the stack frame */
	ret = setup_rt_frame(ksig, oldset, regs);

	signal_setup_done(ret, ksig, 0);
}