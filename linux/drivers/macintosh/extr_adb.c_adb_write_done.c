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
struct adbdev_state {int complete; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_queue; struct adbdev_state* next; struct adbdev_state* completed; int /*<<< orphan*/  n_pending; int /*<<< orphan*/  inuse; scalar_t__ reply_len; scalar_t__ arg; } ;
struct adb_request {int complete; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_queue; struct adb_request* next; struct adb_request* completed; int /*<<< orphan*/  n_pending; int /*<<< orphan*/  inuse; scalar_t__ reply_len; scalar_t__ arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct adbdev_state*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adb_write_done(struct adb_request *req)
{
	struct adbdev_state *state = (struct adbdev_state *) req->arg;
	unsigned long flags;

	if (!req->complete) {
		req->reply_len = 0;
		req->complete = 1;
	}
	spin_lock_irqsave(&state->lock, flags);
	atomic_dec(&state->n_pending);
	if (!state->inuse) {
		kfree(req);
		if (atomic_read(&state->n_pending) == 0) {
			spin_unlock_irqrestore(&state->lock, flags);
			kfree(state);
			return;
		}
	} else {
		struct adb_request **ap = &state->completed;
		while (*ap != NULL)
			ap = &(*ap)->next;
		req->next = NULL;
		*ap = req;
		wake_up_interruptible(&state->wait_queue);
	}
	spin_unlock_irqrestore(&state->lock, flags);
}