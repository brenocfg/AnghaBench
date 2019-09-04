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
typedef  scalar_t__ uint32_t ;
struct binder_transaction {int flags; int /*<<< orphan*/  debug_id; struct binder_transaction* from_parent; } ;
struct TYPE_3__ {scalar_t__ cmd; int /*<<< orphan*/  work; } ;
struct binder_thread {TYPE_2__* proc; TYPE_1__ reply_error; int /*<<< orphan*/  wait; int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEBUG_DEAD_BINDER ; 
 int /*<<< orphan*/  BINDER_DEBUG_FAILED_TRANSACTION ; 
 scalar_t__ BR_OK ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int TF_ONE_WAY ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  binder_enqueue_thread_work_ilocked (struct binder_thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_free_transaction (struct binder_transaction*) ; 
 struct binder_thread* binder_get_txn_from_and_acq_inner (struct binder_transaction*) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  binder_pop_transaction_ilocked (struct binder_thread*,struct binder_transaction*) ; 
 int /*<<< orphan*/  binder_thread_dec_tmpref (struct binder_thread*) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void binder_send_failed_reply(struct binder_transaction *t,
				     uint32_t error_code)
{
	struct binder_thread *target_thread;
	struct binder_transaction *next;

	BUG_ON(t->flags & TF_ONE_WAY);
	while (1) {
		target_thread = binder_get_txn_from_and_acq_inner(t);
		if (target_thread) {
			binder_debug(BINDER_DEBUG_FAILED_TRANSACTION,
				     "send failed reply for transaction %d to %d:%d\n",
				      t->debug_id,
				      target_thread->proc->pid,
				      target_thread->pid);

			binder_pop_transaction_ilocked(target_thread, t);
			if (target_thread->reply_error.cmd == BR_OK) {
				target_thread->reply_error.cmd = error_code;
				binder_enqueue_thread_work_ilocked(
					target_thread,
					&target_thread->reply_error.work);
				wake_up_interruptible(&target_thread->wait);
			} else {
				/*
				 * Cannot get here for normal operation, but
				 * we can if multiple synchronous transactions
				 * are sent without blocking for responses.
				 * Just ignore the 2nd error in this case.
				 */
				pr_warn("Unexpected reply error: %u\n",
					target_thread->reply_error.cmd);
			}
			binder_inner_proc_unlock(target_thread->proc);
			binder_thread_dec_tmpref(target_thread);
			binder_free_transaction(t);
			return;
		}
		next = t->from_parent;

		binder_debug(BINDER_DEBUG_FAILED_TRANSACTION,
			     "send failed reply for transaction %d, target dead\n",
			     t->debug_id);

		binder_free_transaction(t);
		if (next == NULL) {
			binder_debug(BINDER_DEBUG_DEAD_BINDER,
				     "reply failed, no target thread at root\n");
			return;
		}
		t = next;
		binder_debug(BINDER_DEBUG_DEAD_BINDER,
			     "reply failed, no target thread -- retry %d\n",
			      t->debug_id);
	}
}