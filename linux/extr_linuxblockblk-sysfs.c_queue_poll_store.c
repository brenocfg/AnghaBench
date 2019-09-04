#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request_queue {TYPE_1__* mq_ops; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  poll; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  QUEUE_FLAG_POLL ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 scalar_t__ queue_var_store (unsigned long*,char const*,size_t) ; 

__attribute__((used)) static ssize_t queue_poll_store(struct request_queue *q, const char *page,
				size_t count)
{
	unsigned long poll_on;
	ssize_t ret;

	if (!q->mq_ops || !q->mq_ops->poll)
		return -EINVAL;

	ret = queue_var_store(&poll_on, page, count);
	if (ret < 0)
		return ret;

	if (poll_on)
		blk_queue_flag_set(QUEUE_FLAG_POLL, q);
	else
		blk_queue_flag_clear(QUEUE_FLAG_POLL, q);

	return ret;
}