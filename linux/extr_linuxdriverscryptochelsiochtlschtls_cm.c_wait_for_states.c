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
struct socket_wq {int /*<<< orphan*/  rcu; int /*<<< orphan*/ * fasync_list; int /*<<< orphan*/  wait; } ;
struct sock {int /*<<< orphan*/ * sk_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ *,struct socket_wq*) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_rcu_head_on_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct socket_wq* rcu_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_in_state (struct sock*,unsigned int) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int wait_for_states(struct sock *sk, unsigned int states)
{
	DECLARE_WAITQUEUE(wait, current);
	struct socket_wq _sk_wq;
	long current_timeo;
	int err = 0;

	current_timeo = 200;

	/*
	 * We want this to work even when there's no associated struct socket.
	 * In that case we provide a temporary wait_queue_head_t.
	 */
	if (!sk->sk_wq) {
		init_waitqueue_head(&_sk_wq.wait);
		_sk_wq.fasync_list = NULL;
		init_rcu_head_on_stack(&_sk_wq.rcu);
		RCU_INIT_POINTER(sk->sk_wq, &_sk_wq);
	}

	add_wait_queue(sk_sleep(sk), &wait);
	while (!sk_in_state(sk, states)) {
		if (!current_timeo) {
			err = -EBUSY;
			break;
		}
		if (signal_pending(current)) {
			err = sock_intr_errno(current_timeo);
			break;
		}
		set_current_state(TASK_UNINTERRUPTIBLE);
		release_sock(sk);
		if (!sk_in_state(sk, states))
			current_timeo = schedule_timeout(current_timeo);
		__set_current_state(TASK_RUNNING);
		lock_sock(sk);
	}
	remove_wait_queue(sk_sleep(sk), &wait);

	if (rcu_dereference(sk->sk_wq) == &_sk_wq)
		sk->sk_wq = NULL;
	return err;
}