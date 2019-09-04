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
struct xpc_channel {int flags; scalar_t__ reason; int /*<<< orphan*/  n_on_msg_allocate_wq; int /*<<< orphan*/  msg_allocate_wq; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int XPC_C_DISCONNECTING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int schedule_timeout (int) ; 
 int /*<<< orphan*/  wait ; 
 scalar_t__ xpInterrupted ; 
 int xpTimeout ; 

enum xp_retval
xpc_allocate_msg_wait(struct xpc_channel *ch)
{
	enum xp_retval ret;
	DEFINE_WAIT(wait);

	if (ch->flags & XPC_C_DISCONNECTING) {
		DBUG_ON(ch->reason == xpInterrupted);
		return ch->reason;
	}

	atomic_inc(&ch->n_on_msg_allocate_wq);
	prepare_to_wait(&ch->msg_allocate_wq, &wait, TASK_INTERRUPTIBLE);
	ret = schedule_timeout(1);
	finish_wait(&ch->msg_allocate_wq, &wait);
	atomic_dec(&ch->n_on_msg_allocate_wq);

	if (ch->flags & XPC_C_DISCONNECTING) {
		ret = ch->reason;
		DBUG_ON(ch->reason == xpInterrupted);
	} else if (ret == 0) {
		ret = xpTimeout;
	} else {
		ret = xpInterrupted;
	}

	return ret;
}