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
struct fsg_common {int state; int /*<<< orphan*/  lock; scalar_t__ thread_task; void* exception_arg; int /*<<< orphan*/  ep0_req_tag; int /*<<< orphan*/  exception_req_tag; } ;
typedef  enum fsg_state { ____Placeholder_fsg_state } fsg_state ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_SIG_PRIV ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  send_sig_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __raise_exception(struct fsg_common *common, enum fsg_state new_state,
			      void *arg)
{
	unsigned long		flags;

	/*
	 * Do nothing if a higher-priority exception is already in progress.
	 * If a lower-or-equal priority exception is in progress, preempt it
	 * and notify the main thread by sending it a signal.
	 */
	spin_lock_irqsave(&common->lock, flags);
	if (common->state <= new_state) {
		common->exception_req_tag = common->ep0_req_tag;
		common->state = new_state;
		common->exception_arg = arg;
		if (common->thread_task)
			send_sig_info(SIGUSR1, SEND_SIG_PRIV,
				      common->thread_task);
	}
	spin_unlock_irqrestore(&common->lock, flags);
}