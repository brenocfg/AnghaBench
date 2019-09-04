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
struct request {TYPE_1__* q; } ;
struct mapped_device {size_t last_rq_rw; int /*<<< orphan*/  stats; int /*<<< orphan*/  last_rq_start_time; int /*<<< orphan*/  last_rq_pos; scalar_t__ seq_rq_merge_deadline_usecs; int /*<<< orphan*/ * pending; } ;
struct dm_rq_target_io {int /*<<< orphan*/  stats_aux; int /*<<< orphan*/  n_sectors; int /*<<< orphan*/  duration_jiffies; } ;
struct TYPE_2__ {int /*<<< orphan*/  mq_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  dm_get (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_stats_account_io (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_stats_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 size_t rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  rq_end_sector (struct request*) ; 
 struct dm_rq_target_io* tio_from_request (struct request*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_start_request(struct mapped_device *md, struct request *orig)
{
	if (!orig->q->mq_ops)
		blk_start_request(orig);
	else
		blk_mq_start_request(orig);
	atomic_inc(&md->pending[rq_data_dir(orig)]);

	if (md->seq_rq_merge_deadline_usecs) {
		md->last_rq_pos = rq_end_sector(orig);
		md->last_rq_rw = rq_data_dir(orig);
		md->last_rq_start_time = ktime_get();
	}

	if (unlikely(dm_stats_used(&md->stats))) {
		struct dm_rq_target_io *tio = tio_from_request(orig);
		tio->duration_jiffies = jiffies;
		tio->n_sectors = blk_rq_sectors(orig);
		dm_stats_account_io(&md->stats, rq_data_dir(orig),
				    blk_rq_pos(orig), tio->n_sectors, false, 0,
				    &tio->stats_aux);
	}

	/*
	 * Hold the md reference here for the in-flight I/O.
	 * We can't rely on the reference count by device opener,
	 * because the device may be closed during the request completion
	 * when all bios are completed.
	 * See the comment in rq_completed() too.
	 */
	dm_get(md);
}