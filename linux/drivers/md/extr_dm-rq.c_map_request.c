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
struct request {int /*<<< orphan*/  q; } ;
struct mapped_device {int dummy; } ;
struct dm_target {TYPE_1__* type; } ;
struct dm_rq_target_io {int /*<<< orphan*/ * clone; int /*<<< orphan*/  info; struct dm_target* ti; struct request* orig; struct mapped_device* md; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int (* clone_and_map_rq ) (struct dm_target*,struct request*,int /*<<< orphan*/ *,struct request**) ;int /*<<< orphan*/  (* release_clone_rq ) (struct request*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_DEV_RESOURCE ; 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DMWARN (char*,int) ; 
#define  DM_MAPIO_DELAY_REQUEUE 132 
#define  DM_MAPIO_KILL 131 
#define  DM_MAPIO_REMAPPED 130 
#define  DM_MAPIO_REQUEUE 129 
#define  DM_MAPIO_SUBMITTED 128 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  blk_mq_cleanup_rq (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  blk_rq_unprep_clone (struct request*) ; 
 int /*<<< orphan*/  disk_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_disk (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_dispatch_clone_request (struct request*,struct request*) ; 
 int /*<<< orphan*/  dm_kill_unmapped_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_requeue_original_request (struct dm_rq_target_io*,int) ; 
 int /*<<< orphan*/  setup_clone (struct request*,struct request*,struct dm_rq_target_io*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dm_target*,struct request*,int /*<<< orphan*/ *,struct request**) ; 
 int /*<<< orphan*/  stub2 (struct request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_block_rq_remap (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int map_request(struct dm_rq_target_io *tio)
{
	int r;
	struct dm_target *ti = tio->ti;
	struct mapped_device *md = tio->md;
	struct request *rq = tio->orig;
	struct request *clone = NULL;
	blk_status_t ret;

	r = ti->type->clone_and_map_rq(ti, rq, &tio->info, &clone);
	switch (r) {
	case DM_MAPIO_SUBMITTED:
		/* The target has taken the I/O to submit by itself later */
		break;
	case DM_MAPIO_REMAPPED:
		if (setup_clone(clone, rq, tio, GFP_ATOMIC)) {
			/* -ENOMEM */
			ti->type->release_clone_rq(clone, &tio->info);
			return DM_MAPIO_REQUEUE;
		}

		/* The target has remapped the I/O so dispatch it */
		trace_block_rq_remap(clone->q, clone, disk_devt(dm_disk(md)),
				     blk_rq_pos(rq));
		ret = dm_dispatch_clone_request(clone, rq);
		if (ret == BLK_STS_RESOURCE || ret == BLK_STS_DEV_RESOURCE) {
			blk_rq_unprep_clone(clone);
			blk_mq_cleanup_rq(clone);
			tio->ti->type->release_clone_rq(clone, &tio->info);
			tio->clone = NULL;
			return DM_MAPIO_REQUEUE;
		}
		break;
	case DM_MAPIO_REQUEUE:
		/* The target wants to requeue the I/O */
		break;
	case DM_MAPIO_DELAY_REQUEUE:
		/* The target wants to requeue the I/O after a delay */
		dm_requeue_original_request(tio, true);
		break;
	case DM_MAPIO_KILL:
		/* The target wants to complete the I/O */
		dm_kill_unmapped_request(rq, BLK_STS_IOERR);
		break;
	default:
		DMWARN("unimplemented target map return value: %d", r);
		BUG();
	}

	return r;
}