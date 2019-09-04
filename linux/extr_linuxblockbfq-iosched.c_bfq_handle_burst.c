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
struct TYPE_2__ {scalar_t__ parent; } ;
struct bfq_queue {TYPE_1__ entity; scalar_t__ split_time; int /*<<< orphan*/  burst_list_node; } ;
struct bfq_data {scalar_t__ burst_parent_entity; int large_burst; scalar_t__ last_ins_in_burst; scalar_t__ bfq_burst_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_add_to_burst (struct bfq_data*,struct bfq_queue*) ; 
 scalar_t__ bfq_bfqq_in_large_burst (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_mark_bfqq_in_large_burst (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_reset_burst_list (struct bfq_data*,struct bfq_queue*) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 scalar_t__ time_is_after_eq_jiffies (scalar_t__) ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 

__attribute__((used)) static void bfq_handle_burst(struct bfq_data *bfqd, struct bfq_queue *bfqq)
{
	/*
	 * If bfqq is already in the burst list or is part of a large
	 * burst, or finally has just been split, then there is
	 * nothing else to do.
	 */
	if (!hlist_unhashed(&bfqq->burst_list_node) ||
	    bfq_bfqq_in_large_burst(bfqq) ||
	    time_is_after_eq_jiffies(bfqq->split_time +
				     msecs_to_jiffies(10)))
		return;

	/*
	 * If bfqq's creation happens late enough, or bfqq belongs to
	 * a different group than the burst group, then the current
	 * burst is finished, and related data structures must be
	 * reset.
	 *
	 * In this respect, consider the special case where bfqq is
	 * the very first queue created after BFQ is selected for this
	 * device. In this case, last_ins_in_burst and
	 * burst_parent_entity are not yet significant when we get
	 * here. But it is easy to verify that, whether or not the
	 * following condition is true, bfqq will end up being
	 * inserted into the burst list. In particular the list will
	 * happen to contain only bfqq. And this is exactly what has
	 * to happen, as bfqq may be the first queue of the first
	 * burst.
	 */
	if (time_is_before_jiffies(bfqd->last_ins_in_burst +
	    bfqd->bfq_burst_interval) ||
	    bfqq->entity.parent != bfqd->burst_parent_entity) {
		bfqd->large_burst = false;
		bfq_reset_burst_list(bfqd, bfqq);
		goto end;
	}

	/*
	 * If we get here, then bfqq is being activated shortly after the
	 * last queue. So, if the current burst is also large, we can mark
	 * bfqq as belonging to this large burst immediately.
	 */
	if (bfqd->large_burst) {
		bfq_mark_bfqq_in_large_burst(bfqq);
		goto end;
	}

	/*
	 * If we get here, then a large-burst state has not yet been
	 * reached, but bfqq is being activated shortly after the last
	 * queue. Then we add bfqq to the burst.
	 */
	bfq_add_to_burst(bfqd, bfqq);
end:
	/*
	 * At this point, bfqq either has been added to the current
	 * burst or has caused the current burst to terminate and a
	 * possible new burst to start. In particular, in the second
	 * case, bfqq has become the first queue in the possible new
	 * burst.  In both cases last_ins_in_burst needs to be moved
	 * forward.
	 */
	bfqd->last_ins_in_burst = jiffies;
}