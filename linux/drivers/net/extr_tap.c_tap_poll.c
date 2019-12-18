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
struct TYPE_4__ {int /*<<< orphan*/  wait; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; TYPE_2__ wq; } ;
struct tap_queue {int /*<<< orphan*/  sk; TYPE_1__ sock; int /*<<< orphan*/  ring; } ;
struct file {struct tap_queue* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptr_ring_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ sock_writeable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t tap_poll(struct file *file, poll_table *wait)
{
	struct tap_queue *q = file->private_data;
	__poll_t mask = EPOLLERR;

	if (!q)
		goto out;

	mask = 0;
	poll_wait(file, &q->sock.wq.wait, wait);

	if (!ptr_ring_empty(&q->ring))
		mask |= EPOLLIN | EPOLLRDNORM;

	if (sock_writeable(&q->sk) ||
	    (!test_and_set_bit(SOCKWQ_ASYNC_NOSPACE, &q->sock.flags) &&
	     sock_writeable(&q->sk)))
		mask |= EPOLLOUT | EPOLLWRNORM;

out:
	return mask;
}