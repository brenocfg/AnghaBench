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
struct tap_queue {int enabled; int queue_index; int /*<<< orphan*/  tap; } ;
struct tap_dev {int numvtaps; int /*<<< orphan*/ * taps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tap_queue*) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tap_disable_queue(struct tap_queue *q)
{
	struct tap_dev *tap;
	struct tap_queue *nq;

	ASSERT_RTNL();
	if (!q->enabled)
		return -EINVAL;

	tap = rtnl_dereference(q->tap);

	if (tap) {
		int index = q->queue_index;
		BUG_ON(index >= tap->numvtaps);
		nq = rtnl_dereference(tap->taps[tap->numvtaps - 1]);
		nq->queue_index = index;

		rcu_assign_pointer(tap->taps[index], nq);
		RCU_INIT_POINTER(tap->taps[tap->numvtaps - 1], NULL);
		q->enabled = false;

		tap->numvtaps--;
	}

	return 0;
}