#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union map_info {int dummy; } map_info ;
struct request_queue {int dummy; } ;
struct request {int cmd_flags; int /*<<< orphan*/  rq_disk; int /*<<< orphan*/ * biotail; int /*<<< orphan*/  bio; } ;
struct TYPE_10__ {TYPE_1__* dev; } ;
struct pgpath {TYPE_5__ path; TYPE_3__* pg; } ;
struct multipath {int /*<<< orphan*/  pg_init_in_progress; int /*<<< orphan*/  flags; int /*<<< orphan*/  current_pgpath; } ;
struct dm_target {struct multipath* private; } ;
struct dm_mpath_io {size_t nr_bytes; struct pgpath* pgpath; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
struct TYPE_9__ {TYPE_2__* type; } ;
struct TYPE_8__ {TYPE_4__ ps; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* start_io ) (TYPE_4__*,TYPE_5__*,size_t) ;} ;
struct TYPE_6__ {struct block_device* bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_REQ_NOWAIT ; 
 int DM_MAPIO_DELAY_REQUEUE ; 
 int DM_MAPIO_KILL ; 
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_REQUEUE ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int /*<<< orphan*/  MPATHF_PG_INIT_REQUIRED ; 
 int /*<<< orphan*/  MPATHF_QUEUE_IO ; 
 struct pgpath* READ_ONCE (int /*<<< orphan*/ ) ; 
 int REQ_FAILFAST_TRANSPORT ; 
 int REQ_NOMERGE ; 
 int /*<<< orphan*/  activate_or_offline_path (struct pgpath*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 struct request* blk_get_request (struct request_queue*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_queue_dying (struct request_queue*) ; 
 size_t blk_rq_bytes (struct request*) ; 
 struct pgpath* choose_pgpath (struct multipath*,size_t) ; 
 int /*<<< orphan*/  dm_report_EIO (struct multipath*) ; 
 struct dm_mpath_io* get_mpio (union map_info*) ; 
 scalar_t__ must_push_back_rq (struct multipath*) ; 
 int /*<<< orphan*/  pg_init_all_paths (struct multipath*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_5__*,size_t) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int multipath_clone_and_map(struct dm_target *ti, struct request *rq,
				   union map_info *map_context,
				   struct request **__clone)
{
	struct multipath *m = ti->private;
	size_t nr_bytes = blk_rq_bytes(rq);
	struct pgpath *pgpath;
	struct block_device *bdev;
	struct dm_mpath_io *mpio = get_mpio(map_context);
	struct request_queue *q;
	struct request *clone;

	/* Do we need to select a new pgpath? */
	pgpath = READ_ONCE(m->current_pgpath);
	if (!pgpath || !test_bit(MPATHF_QUEUE_IO, &m->flags))
		pgpath = choose_pgpath(m, nr_bytes);

	if (!pgpath) {
		if (must_push_back_rq(m))
			return DM_MAPIO_DELAY_REQUEUE;
		dm_report_EIO(m);	/* Failed */
		return DM_MAPIO_KILL;
	} else if (test_bit(MPATHF_QUEUE_IO, &m->flags) ||
		   test_bit(MPATHF_PG_INIT_REQUIRED, &m->flags)) {
		pg_init_all_paths(m);
		return DM_MAPIO_DELAY_REQUEUE;
	}

	mpio->pgpath = pgpath;
	mpio->nr_bytes = nr_bytes;

	bdev = pgpath->path.dev->bdev;
	q = bdev_get_queue(bdev);
	clone = blk_get_request(q, rq->cmd_flags | REQ_NOMERGE,
			BLK_MQ_REQ_NOWAIT);
	if (IS_ERR(clone)) {
		/* EBUSY, ENODEV or EWOULDBLOCK: requeue */
		if (blk_queue_dying(q)) {
			atomic_inc(&m->pg_init_in_progress);
			activate_or_offline_path(pgpath);
			return DM_MAPIO_DELAY_REQUEUE;
		}

		/*
		 * blk-mq's SCHED_RESTART can cover this requeue, so we
		 * needn't deal with it by DELAY_REQUEUE. More importantly,
		 * we have to return DM_MAPIO_REQUEUE so that blk-mq can
		 * get the queue busy feedback (via BLK_STS_RESOURCE),
		 * otherwise I/O merging can suffer.
		 */
		return DM_MAPIO_REQUEUE;
	}
	clone->bio = clone->biotail = NULL;
	clone->rq_disk = bdev->bd_disk;
	clone->cmd_flags |= REQ_FAILFAST_TRANSPORT;
	*__clone = clone;

	if (pgpath->pg->ps.type->start_io)
		pgpath->pg->ps.type->start_io(&pgpath->pg->ps,
					      &pgpath->path,
					      nr_bytes);
	return DM_MAPIO_REMAPPED;
}