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
struct smi_info {int /*<<< orphan*/  si_lock; struct ipmi_smi_msg* waiting_msg; scalar_t__ run_to_completion; } ;
struct ipmi_smi_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct ipmi_smi_msg*) ; 
 int /*<<< orphan*/  check_start_timer_thread (struct smi_info*) ; 
 int /*<<< orphan*/  debug_timestamp (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sender(void                *send_info,
		   struct ipmi_smi_msg *msg)
{
	struct smi_info   *smi_info = send_info;
	unsigned long     flags;

	debug_timestamp("Enqueue");

	if (smi_info->run_to_completion) {
		/*
		 * If we are running to completion, start it.  Upper
		 * layer will call flush_messages to clear it out.
		 */
		smi_info->waiting_msg = msg;
		return;
	}

	spin_lock_irqsave(&smi_info->si_lock, flags);
	/*
	 * The following two lines don't need to be under the lock for
	 * the lock's sake, but they do need SMP memory barriers to
	 * avoid getting things out of order.  We are already claiming
	 * the lock, anyway, so just do it under the lock to avoid the
	 * ordering problem.
	 */
	BUG_ON(smi_info->waiting_msg);
	smi_info->waiting_msg = msg;
	check_start_timer_thread(smi_info);
	spin_unlock_irqrestore(&smi_info->si_lock, flags);
}