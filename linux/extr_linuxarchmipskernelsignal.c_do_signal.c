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
struct pt_regs {int* regs; int cp0_epc; } ;
struct ksignal {int dummy; } ;
struct TYPE_5__ {TYPE_1__* abi; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;
struct TYPE_4__ {int restart; } ;

/* Variables and functions */
#define  ERESTARTNOHAND 131 
#define  ERESTARTNOINTR 130 
#define  ERESTARTSYS 129 
#define  ERESTART_RESTARTBLOCK 128 
 TYPE_3__* current ; 
 scalar_t__ get_signal (struct ksignal*) ; 
 int /*<<< orphan*/  handle_signal (struct ksignal*,struct pt_regs*) ; 
 int /*<<< orphan*/  restore_saved_sigmask () ; 

__attribute__((used)) static void do_signal(struct pt_regs *regs)
{
	struct ksignal ksig;

	if (get_signal(&ksig)) {
		/* Whee!  Actually deliver the signal.	*/
		handle_signal(&ksig, regs);
		return;
	}

	if (regs->regs[0]) {
		switch (regs->regs[2]) {
		case ERESTARTNOHAND:
		case ERESTARTSYS:
		case ERESTARTNOINTR:
			regs->regs[2] = regs->regs[0];
			regs->regs[7] = regs->regs[26];
			regs->cp0_epc -= 4;
			break;

		case ERESTART_RESTARTBLOCK:
			regs->regs[2] = current->thread.abi->restart;
			regs->regs[7] = regs->regs[26];
			regs->cp0_epc -= 4;
			break;
		}
		regs->regs[0] = 0;	/* Don't deal with this again.	*/
	}

	/*
	 * If there's no signal to deliver, we just put the saved sigmask
	 * back
	 */
	restore_saved_sigmask();
}