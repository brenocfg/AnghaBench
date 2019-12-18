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
struct tap_queue {int /*<<< orphan*/  sk; int /*<<< orphan*/  ring; } ;
struct sk_buff {int dummy; } ;
struct iov_iter {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sk_buff* ptr_ring_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tap_put_user (struct tap_queue*,struct sk_buff*,struct iov_iter*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static ssize_t tap_do_read(struct tap_queue *q,
			   struct iov_iter *to,
			   int noblock, struct sk_buff *skb)
{
	DEFINE_WAIT(wait);
	ssize_t ret = 0;

	if (!iov_iter_count(to)) {
		kfree_skb(skb);
		return 0;
	}

	if (skb)
		goto put;

	while (1) {
		if (!noblock)
			prepare_to_wait(sk_sleep(&q->sk), &wait,
					TASK_INTERRUPTIBLE);

		/* Read frames from the queue */
		skb = ptr_ring_consume(&q->ring);
		if (skb)
			break;
		if (noblock) {
			ret = -EAGAIN;
			break;
		}
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}
		/* Nothing to read, let's sleep */
		schedule();
	}
	if (!noblock)
		finish_wait(sk_sleep(&q->sk), &wait);

put:
	if (skb) {
		ret = tap_put_user(q, skb, to);
		if (unlikely(ret < 0))
			kfree_skb(skb);
		else
			consume_skb(skb);
	}
	return ret;
}