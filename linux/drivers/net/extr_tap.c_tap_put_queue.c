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
struct tap_queue {int /*<<< orphan*/  sk; int /*<<< orphan*/  next; int /*<<< orphan*/  tap; scalar_t__ enabled; } ;
struct tap_dev {int /*<<< orphan*/  numqueues; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct tap_dev* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  tap_disable_queue (struct tap_queue*) ; 

__attribute__((used)) static void tap_put_queue(struct tap_queue *q)
{
	struct tap_dev *tap;

	rtnl_lock();
	tap = rtnl_dereference(q->tap);

	if (tap) {
		if (q->enabled)
			BUG_ON(tap_disable_queue(q));

		tap->numqueues--;
		RCU_INIT_POINTER(q->tap, NULL);
		sock_put(&q->sk);
		list_del_init(&q->next);
	}

	rtnl_unlock();

	synchronize_rcu();
	sock_put(&q->sk);
}