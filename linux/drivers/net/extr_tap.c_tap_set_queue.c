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
struct tap_queue {scalar_t__ numqueues; size_t numvtaps; size_t queue_index; int enabled; int /*<<< orphan*/  queue_list; int /*<<< orphan*/  next; struct file* file; int /*<<< orphan*/  sk; int /*<<< orphan*/ * taps; int /*<<< orphan*/  tap; } ;
struct tap_dev {scalar_t__ numqueues; size_t numvtaps; size_t queue_index; int enabled; int /*<<< orphan*/  queue_list; int /*<<< orphan*/  next; struct file* file; int /*<<< orphan*/  sk; int /*<<< orphan*/ * taps; int /*<<< orphan*/  tap; } ;
struct file {struct tap_queue* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ MAX_TAP_QUEUES ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tap_queue*) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tap_set_queue(struct tap_dev *tap, struct file *file,
			 struct tap_queue *q)
{
	if (tap->numqueues == MAX_TAP_QUEUES)
		return -EBUSY;

	rcu_assign_pointer(q->tap, tap);
	rcu_assign_pointer(tap->taps[tap->numvtaps], q);
	sock_hold(&q->sk);

	q->file = file;
	q->queue_index = tap->numvtaps;
	q->enabled = true;
	file->private_data = q;
	list_add_tail(&q->next, &tap->queue_list);

	tap->numvtaps++;
	tap->numqueues++;

	return 0;
}