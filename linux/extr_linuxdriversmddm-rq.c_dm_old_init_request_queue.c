#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mapped_device {int init_tio_pdu; int /*<<< orphan*/ * kworker_task; int /*<<< orphan*/  kworker; TYPE_1__* queue; scalar_t__ seq_rq_merge_deadline_usecs; } ;
struct dm_target {scalar_t__ per_io_data_size; } ;
struct dm_table {int dummy; } ;
struct dm_rq_target_io {int dummy; } ;
struct TYPE_3__ {int cmd_size; int /*<<< orphan*/  init_rq_fn; int /*<<< orphan*/  request_fn; struct mapped_device* rq_alloc_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ blk_init_allocated_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_queue_softirq_done (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_device_name (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_old_request_fn ; 
 int /*<<< orphan*/  dm_rq_init_rq ; 
 int /*<<< orphan*/  dm_softirq_done ; 
 struct dm_target* dm_table_get_immutable_target (struct dm_table*) ; 
 int /*<<< orphan*/  kthread_init_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_worker_fn ; 

int dm_old_init_request_queue(struct mapped_device *md, struct dm_table *t)
{
	struct dm_target *immutable_tgt;

	/* Fully initialize the queue */
	md->queue->cmd_size = sizeof(struct dm_rq_target_io);
	md->queue->rq_alloc_data = md;
	md->queue->request_fn = dm_old_request_fn;
	md->queue->init_rq_fn = dm_rq_init_rq;

	immutable_tgt = dm_table_get_immutable_target(t);
	if (immutable_tgt && immutable_tgt->per_io_data_size) {
		/* any target-specific per-io data is immediately after the tio */
		md->queue->cmd_size += immutable_tgt->per_io_data_size;
		md->init_tio_pdu = true;
	}
	if (blk_init_allocated_queue(md->queue) < 0)
		return -EINVAL;

	/* disable dm_old_request_fn's merge heuristic by default */
	md->seq_rq_merge_deadline_usecs = 0;

	blk_queue_softirq_done(md->queue, dm_softirq_done);

	/* Initialize the request-based DM worker thread */
	kthread_init_worker(&md->kworker);
	md->kworker_task = kthread_run(kthread_worker_fn, &md->kworker,
				       "kdmwork-%s", dm_device_name(md));
	if (IS_ERR(md->kworker_task)) {
		int error = PTR_ERR(md->kworker_task);
		md->kworker_task = NULL;
		return error;
	}

	return 0;
}