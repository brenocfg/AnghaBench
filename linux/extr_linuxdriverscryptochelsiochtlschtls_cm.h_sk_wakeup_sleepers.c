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
struct socket_wq {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_wq; } ;

/* Variables and functions */
 struct socket_wq* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 scalar_t__ skwq_has_sleeper (struct socket_wq*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sk_wakeup_sleepers(struct sock *sk, bool interruptable)
{
	struct socket_wq *wq;

	rcu_read_lock();
	wq = rcu_dereference(sk->sk_wq);
	if (skwq_has_sleeper(wq)) {
		if (interruptable)
			wake_up_interruptible(sk_sleep(sk));
		else
			wake_up_all(sk_sleep(sk));
	}
	rcu_read_unlock();
}