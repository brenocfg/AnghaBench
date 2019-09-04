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
struct request_queue {struct mapped_device* queuedata; } ;
struct request {scalar_t__ bio; } ;
struct mapped_device {scalar_t__ last_rq_pos; scalar_t__ last_rq_rw; int /*<<< orphan*/  kworker; struct dm_target* immutable_target; } ;
struct dm_target {TYPE_1__* type; } ;
struct dm_table {int dummy; } ;
struct dm_rq_target_io {int /*<<< orphan*/  work; struct dm_target* ti; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {scalar_t__ (* busy ) (struct dm_target*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ REQ_OP_FLUSH ; 
 int /*<<< orphan*/  bio_multiple_segments (scalar_t__) ; 
 int /*<<< orphan*/  blk_delay_queue (struct request_queue*,int) ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_stopped (struct request_queue*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 struct dm_table* dm_get_live_table (struct mapped_device*,int*) ; 
 scalar_t__ dm_old_request_peeked_before_merge_deadline (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_put_live_table (struct mapped_device*,int) ; 
 int /*<<< orphan*/  dm_start_request (struct mapped_device*,struct request*) ; 
 struct dm_target* dm_table_find_target (struct dm_table*,scalar_t__) ; 
 int /*<<< orphan*/  init_tio (struct dm_rq_target_io*,struct request*,struct mapped_device*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ md_in_flight (struct mapped_device*) ; 
 scalar_t__ req_op (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 scalar_t__ stub1 (struct dm_target*) ; 
 struct dm_rq_target_io* tio_from_request (struct request*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void dm_old_request_fn(struct request_queue *q)
{
	struct mapped_device *md = q->queuedata;
	struct dm_target *ti = md->immutable_target;
	struct request *rq;
	struct dm_rq_target_io *tio;
	sector_t pos = 0;

	if (unlikely(!ti)) {
		int srcu_idx;
		struct dm_table *map = dm_get_live_table(md, &srcu_idx);

		if (unlikely(!map)) {
			dm_put_live_table(md, srcu_idx);
			return;
		}
		ti = dm_table_find_target(map, pos);
		dm_put_live_table(md, srcu_idx);
	}

	/*
	 * For suspend, check blk_queue_stopped() and increment
	 * ->pending within a single queue_lock not to increment the
	 * number of in-flight I/Os after the queue is stopped in
	 * dm_suspend().
	 */
	while (!blk_queue_stopped(q)) {
		rq = blk_peek_request(q);
		if (!rq)
			return;

		/* always use block 0 to find the target for flushes for now */
		pos = 0;
		if (req_op(rq) != REQ_OP_FLUSH)
			pos = blk_rq_pos(rq);

		if ((dm_old_request_peeked_before_merge_deadline(md) &&
		     md_in_flight(md) && rq->bio && !bio_multiple_segments(rq->bio) &&
		     md->last_rq_pos == pos && md->last_rq_rw == rq_data_dir(rq)) ||
		    (ti->type->busy && ti->type->busy(ti))) {
			blk_delay_queue(q, 10);
			return;
		}

		dm_start_request(md, rq);

		tio = tio_from_request(rq);
		init_tio(tio, rq, md);
		/* Establish tio->ti before queuing work (map_tio_request) */
		tio->ti = ti;
		kthread_queue_work(&md->kworker, &tio->work);
		BUG_ON(!irqs_disabled());
	}
}