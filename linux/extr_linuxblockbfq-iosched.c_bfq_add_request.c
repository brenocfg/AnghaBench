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
struct request {int dummy; } ;
struct TYPE_2__ {int prio_changed; } ;
struct bfq_queue {unsigned int wr_coeff; scalar_t__ last_wr_start_finish; struct request* next_rq; TYPE_1__ entity; int /*<<< orphan*/  wr_cur_max_time; int /*<<< orphan*/  sort_list; int /*<<< orphan*/ * queued; struct bfq_data* bfqd; } ;
struct bfq_data {unsigned int bfq_wr_coeff; scalar_t__ low_latency; int /*<<< orphan*/  wr_busy_queues; scalar_t__ bfq_wr_min_inter_arr_async; int /*<<< orphan*/  last_position; int /*<<< orphan*/  queued; } ;

/* Variables and functions */
 struct bfq_queue* RQ_BFQQ (struct request*) ; 
 int /*<<< orphan*/  bfq_bfqq_busy (struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_bfqq_handle_idle_busy_switch (struct bfq_data*,struct bfq_queue*,unsigned int,struct request*,int*) ; 
 struct request* bfq_choose_req (struct bfq_data*,struct request*,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_log_bfqq (struct bfq_data*,struct bfq_queue*,char*,size_t) ; 
 int /*<<< orphan*/  bfq_pos_tree_add_move (struct bfq_data*,struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_updated_next_req (struct bfq_data*,struct bfq_queue*) ; 
 int /*<<< orphan*/  bfq_wr_duration (struct bfq_data*) ; 
 int /*<<< orphan*/  elv_rb_add (int /*<<< orphan*/ *,struct request*) ; 
 scalar_t__ jiffies ; 
 size_t rq_is_sync (struct request*) ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 

__attribute__((used)) static void bfq_add_request(struct request *rq)
{
	struct bfq_queue *bfqq = RQ_BFQQ(rq);
	struct bfq_data *bfqd = bfqq->bfqd;
	struct request *next_rq, *prev;
	unsigned int old_wr_coeff = bfqq->wr_coeff;
	bool interactive = false;

	bfq_log_bfqq(bfqd, bfqq, "add_request %d", rq_is_sync(rq));
	bfqq->queued[rq_is_sync(rq)]++;
	bfqd->queued++;

	elv_rb_add(&bfqq->sort_list, rq);

	/*
	 * Check if this request is a better next-serve candidate.
	 */
	prev = bfqq->next_rq;
	next_rq = bfq_choose_req(bfqd, bfqq->next_rq, rq, bfqd->last_position);
	bfqq->next_rq = next_rq;

	/*
	 * Adjust priority tree position, if next_rq changes.
	 */
	if (prev != bfqq->next_rq)
		bfq_pos_tree_add_move(bfqd, bfqq);

	if (!bfq_bfqq_busy(bfqq)) /* switching to busy ... */
		bfq_bfqq_handle_idle_busy_switch(bfqd, bfqq, old_wr_coeff,
						 rq, &interactive);
	else {
		if (bfqd->low_latency && old_wr_coeff == 1 && !rq_is_sync(rq) &&
		    time_is_before_jiffies(
				bfqq->last_wr_start_finish +
				bfqd->bfq_wr_min_inter_arr_async)) {
			bfqq->wr_coeff = bfqd->bfq_wr_coeff;
			bfqq->wr_cur_max_time = bfq_wr_duration(bfqd);

			bfqd->wr_busy_queues++;
			bfqq->entity.prio_changed = 1;
		}
		if (prev != bfqq->next_rq)
			bfq_updated_next_req(bfqd, bfqq);
	}

	/*
	 * Assign jiffies to last_wr_start_finish in the following
	 * cases:
	 *
	 * . if bfqq is not going to be weight-raised, because, for
	 *   non weight-raised queues, last_wr_start_finish stores the
	 *   arrival time of the last request; as of now, this piece
	 *   of information is used only for deciding whether to
	 *   weight-raise async queues
	 *
	 * . if bfqq is not weight-raised, because, if bfqq is now
	 *   switching to weight-raised, then last_wr_start_finish
	 *   stores the time when weight-raising starts
	 *
	 * . if bfqq is interactive, because, regardless of whether
	 *   bfqq is currently weight-raised, the weight-raising
	 *   period must start or restart (this case is considered
	 *   separately because it is not detected by the above
	 *   conditions, if bfqq is already weight-raised)
	 *
	 * last_wr_start_finish has to be updated also if bfqq is soft
	 * real-time, because the weight-raising period is constantly
	 * restarted on idle-to-busy transitions for these queues, but
	 * this is already done in bfq_bfqq_handle_idle_busy_switch if
	 * needed.
	 */
	if (bfqd->low_latency &&
		(old_wr_coeff == 1 || bfqq->wr_coeff == 1 || interactive))
		bfqq->last_wr_start_finish = jiffies;
}