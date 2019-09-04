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
struct request {scalar_t__ fifo_time; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct bfq_queue {int /*<<< orphan*/  bfqd; TYPE_1__ fifo; } ;

/* Variables and functions */
 scalar_t__ bfq_bfqq_fifo_expire (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (int /*<<< orphan*/ ,struct bfq_queue*,char*,struct request*) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_fifo_expire (struct bfq_queue*) ; 
 scalar_t__ ktime_get_ns () ; 
 struct request* rq_entry_fifo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct request *bfq_check_fifo(struct bfq_queue *bfqq,
				      struct request *last)
{
	struct request *rq;

	if (bfq_bfqq_fifo_expire(bfqq))
		return NULL;

	bfq_mark_bfqq_fifo_expire(bfqq);

	rq = rq_entry_fifo(bfqq->fifo.next);

	if (rq == last || ktime_get_ns() < rq->fifo_time)
		return NULL;

	bfq_log_bfqq(bfqq->bfqd, bfqq, "check_fifo: returned %p", rq);
	return rq;
}