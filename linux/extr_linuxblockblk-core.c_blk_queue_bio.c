#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue_flags; } ;
struct request {int /*<<< orphan*/  queuelist; int /*<<< orphan*/  cpu; } ;
struct TYPE_4__ {int /*<<< orphan*/  prev; } ;
struct blk_plug {TYPE_1__ list; } ;
struct bio {int /*<<< orphan*/  bi_status; int /*<<< orphan*/  bi_opf; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;
struct TYPE_5__ {struct blk_plug* plug; } ;

/* Variables and functions */
 unsigned int BLK_MAX_REQUEST_COUNT ; 
 scalar_t__ BLK_PLUG_FLUSH_SIZE ; 
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
#define  ELEVATOR_BACK_MERGE 129 
#define  ELEVATOR_FRONT_MERGE 128 
 int ELEVATOR_INSERT_FLUSH ; 
 int ELEVATOR_INSERT_SORT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int /*<<< orphan*/  PTR_ERR (struct request*) ; 
 int /*<<< orphan*/  QUEUE_FLAG_SAME_COMP ; 
 int /*<<< orphan*/  __blk_put_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  __blk_run_queue (struct request_queue*) ; 
 int /*<<< orphan*/  add_acct_request (struct request_queue*,struct request*,int) ; 
 struct request* attempt_back_merge (struct request_queue*,struct request*) ; 
 struct request* attempt_front_merge (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  bio_attempt_back_merge (struct request_queue*,struct request*,struct bio*) ; 
 int /*<<< orphan*/  bio_attempt_front_merge (struct request_queue*,struct request*,struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_integrity_prep (struct bio*) ; 
 int /*<<< orphan*/  blk_account_io_start (struct request*,int) ; 
 scalar_t__ blk_attempt_plug_merge (struct request_queue*,struct bio*,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_flush_plug_list (struct blk_plug*,int) ; 
 int /*<<< orphan*/  blk_init_request_from_bio (struct request*,struct bio*) ; 
 unsigned int blk_plug_queued_count (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_bounce (struct request_queue*,struct bio**) ; 
 int /*<<< orphan*/  blk_queue_enter_live (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_exit (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_nomerges (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_split (struct request_queue*,struct bio**) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  elv_bio_merged (struct request_queue*,struct request*,struct bio*) ; 
 int elv_merge (struct request_queue*,struct request**,struct bio*) ; 
 int /*<<< orphan*/  elv_merged_request (struct request_queue*,struct request*,int const) ; 
 struct request* get_request (struct request_queue*,int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ list_empty (TYPE_1__*) ; 
 struct request* list_entry_rq (int /*<<< orphan*/ ) ; 
 scalar_t__ op_is_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  rq_qos_cleanup (struct request_queue*,struct bio*) ; 
 int /*<<< orphan*/  rq_qos_throttle (struct request_queue*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_qos_track (struct request_queue*,struct request*,struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_block_plug (struct request_queue*) ; 

__attribute__((used)) static blk_qc_t blk_queue_bio(struct request_queue *q, struct bio *bio)
{
	struct blk_plug *plug;
	int where = ELEVATOR_INSERT_SORT;
	struct request *req, *free;
	unsigned int request_count = 0;

	/*
	 * low level driver can indicate that it wants pages above a
	 * certain limit bounced to low memory (ie for highmem, or even
	 * ISA dma in theory)
	 */
	blk_queue_bounce(q, &bio);

	blk_queue_split(q, &bio);

	if (!bio_integrity_prep(bio))
		return BLK_QC_T_NONE;

	if (op_is_flush(bio->bi_opf)) {
		spin_lock_irq(q->queue_lock);
		where = ELEVATOR_INSERT_FLUSH;
		goto get_rq;
	}

	/*
	 * Check if we can merge with the plugged list before grabbing
	 * any locks.
	 */
	if (!blk_queue_nomerges(q)) {
		if (blk_attempt_plug_merge(q, bio, &request_count, NULL))
			return BLK_QC_T_NONE;
	} else
		request_count = blk_plug_queued_count(q);

	spin_lock_irq(q->queue_lock);

	switch (elv_merge(q, &req, bio)) {
	case ELEVATOR_BACK_MERGE:
		if (!bio_attempt_back_merge(q, req, bio))
			break;
		elv_bio_merged(q, req, bio);
		free = attempt_back_merge(q, req);
		if (free)
			__blk_put_request(q, free);
		else
			elv_merged_request(q, req, ELEVATOR_BACK_MERGE);
		goto out_unlock;
	case ELEVATOR_FRONT_MERGE:
		if (!bio_attempt_front_merge(q, req, bio))
			break;
		elv_bio_merged(q, req, bio);
		free = attempt_front_merge(q, req);
		if (free)
			__blk_put_request(q, free);
		else
			elv_merged_request(q, req, ELEVATOR_FRONT_MERGE);
		goto out_unlock;
	default:
		break;
	}

get_rq:
	rq_qos_throttle(q, bio, q->queue_lock);

	/*
	 * Grab a free request. This is might sleep but can not fail.
	 * Returns with the queue unlocked.
	 */
	blk_queue_enter_live(q);
	req = get_request(q, bio->bi_opf, bio, 0, GFP_NOIO);
	if (IS_ERR(req)) {
		blk_queue_exit(q);
		rq_qos_cleanup(q, bio);
		if (PTR_ERR(req) == -ENOMEM)
			bio->bi_status = BLK_STS_RESOURCE;
		else
			bio->bi_status = BLK_STS_IOERR;
		bio_endio(bio);
		goto out_unlock;
	}

	rq_qos_track(q, req, bio);

	/*
	 * After dropping the lock and possibly sleeping here, our request
	 * may now be mergeable after it had proven unmergeable (above).
	 * We don't worry about that case for efficiency. It won't happen
	 * often, and the elevators are able to handle it.
	 */
	blk_init_request_from_bio(req, bio);

	if (test_bit(QUEUE_FLAG_SAME_COMP, &q->queue_flags))
		req->cpu = raw_smp_processor_id();

	plug = current->plug;
	if (plug) {
		/*
		 * If this is the first request added after a plug, fire
		 * of a plug trace.
		 *
		 * @request_count may become stale because of schedule
		 * out, so check plug list again.
		 */
		if (!request_count || list_empty(&plug->list))
			trace_block_plug(q);
		else {
			struct request *last = list_entry_rq(plug->list.prev);
			if (request_count >= BLK_MAX_REQUEST_COUNT ||
			    blk_rq_bytes(last) >= BLK_PLUG_FLUSH_SIZE) {
				blk_flush_plug_list(plug, false);
				trace_block_plug(q);
			}
		}
		list_add_tail(&req->queuelist, &plug->list);
		blk_account_io_start(req, true);
	} else {
		spin_lock_irq(q->queue_lock);
		add_acct_request(q, req, where);
		__blk_run_queue(q);
out_unlock:
		spin_unlock_irq(q->queue_lock);
	}

	return BLK_QC_T_NONE;
}