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
struct request_queue {int /*<<< orphan*/  queue_lock; TYPE_1__* elevator; } ;
struct TYPE_4__ {struct cfq_queue** priv; int /*<<< orphan*/  icq; } ;
struct request {TYPE_2__ elv; } ;
struct cfq_queue {struct cfq_queue* cfqg; int /*<<< orphan*/  ref; int /*<<< orphan*/ * allocated; scalar_t__ new_cfqq; } ;
struct cfq_io_cq {int dummy; } ;
struct cfq_data {struct cfq_queue oom_cfqq; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {struct cfq_data* elevator_data; } ;

/* Variables and functions */
 scalar_t__ cfq_cfqq_coop (struct cfq_queue*) ; 
 scalar_t__ cfq_cfqq_split_coop (struct cfq_queue*) ; 
 struct cfq_queue* cfq_get_queue (struct cfq_data*,int const,struct cfq_io_cq*,struct bio*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*) ; 
 struct cfq_queue* cfq_merge_cfqqs (struct cfq_data*,struct cfq_io_cq*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_put_queue (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfqg_get (struct cfq_queue*) ; 
 int /*<<< orphan*/  check_blkcg_changed (struct cfq_io_cq*,struct bio*) ; 
 int /*<<< orphan*/  check_ioprio_changed (struct cfq_io_cq*,struct bio*) ; 
 int /*<<< orphan*/  cic_set_cfqq (struct cfq_io_cq*,struct cfq_queue*,int const) ; 
 struct cfq_queue* cic_to_cfqq (struct cfq_io_cq*,int const) ; 
 struct cfq_io_cq* icq_to_cic (int /*<<< orphan*/ ) ; 
 int rq_data_dir (struct request*) ; 
 int rq_is_sync (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 struct cfq_queue* split_cfqq (struct cfq_io_cq*,struct cfq_queue*) ; 

__attribute__((used)) static int
cfq_set_request(struct request_queue *q, struct request *rq, struct bio *bio,
		gfp_t gfp_mask)
{
	struct cfq_data *cfqd = q->elevator->elevator_data;
	struct cfq_io_cq *cic = icq_to_cic(rq->elv.icq);
	const int rw = rq_data_dir(rq);
	const bool is_sync = rq_is_sync(rq);
	struct cfq_queue *cfqq;

	spin_lock_irq(q->queue_lock);

	check_ioprio_changed(cic, bio);
	check_blkcg_changed(cic, bio);
new_queue:
	cfqq = cic_to_cfqq(cic, is_sync);
	if (!cfqq || cfqq == &cfqd->oom_cfqq) {
		if (cfqq)
			cfq_put_queue(cfqq);
		cfqq = cfq_get_queue(cfqd, is_sync, cic, bio);
		cic_set_cfqq(cic, cfqq, is_sync);
	} else {
		/*
		 * If the queue was seeky for too long, break it apart.
		 */
		if (cfq_cfqq_coop(cfqq) && cfq_cfqq_split_coop(cfqq)) {
			cfq_log_cfqq(cfqd, cfqq, "breaking apart cfqq");
			cfqq = split_cfqq(cic, cfqq);
			if (!cfqq)
				goto new_queue;
		}

		/*
		 * Check to see if this queue is scheduled to merge with
		 * another, closely cooperating queue.  The merging of
		 * queues happens here as it must be done in process context.
		 * The reference on new_cfqq was taken in merge_cfqqs.
		 */
		if (cfqq->new_cfqq)
			cfqq = cfq_merge_cfqqs(cfqd, cic, cfqq);
	}

	cfqq->allocated[rw]++;

	cfqq->ref++;
	cfqg_get(cfqq->cfqg);
	rq->elv.priv[0] = cfqq;
	rq->elv.priv[1] = cfqq->cfqg;
	spin_unlock_irq(q->queue_lock);

	return 0;
}