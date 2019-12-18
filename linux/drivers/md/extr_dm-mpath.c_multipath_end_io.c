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
typedef  union map_info {int dummy; } map_info ;
struct request {int dummy; } ;
struct pgpath {int /*<<< orphan*/  path; TYPE_1__* pg; } ;
struct path_selector {TYPE_2__* type; } ;
struct multipath {int /*<<< orphan*/  nr_valid_paths; } ;
struct dm_target {struct multipath* private; } ;
struct dm_mpath_io {int /*<<< orphan*/  nr_bytes; struct pgpath* pgpath; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* end_io ) (struct path_selector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct path_selector ps; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_IOERR ; 
 scalar_t__ BLK_STS_RESOURCE ; 
 int DM_ENDIO_DELAY_REQUEUE ; 
 int DM_ENDIO_DONE ; 
 int DM_ENDIO_REQUEUE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ blk_path_error (scalar_t__) ; 
 int /*<<< orphan*/  dm_report_EIO (struct multipath*) ; 
 int /*<<< orphan*/  fail_path (struct pgpath*) ; 
 struct dm_mpath_io* get_mpio (union map_info*) ; 
 int /*<<< orphan*/  must_push_back_rq (struct multipath*) ; 
 int /*<<< orphan*/  stub1 (struct path_selector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int multipath_end_io(struct dm_target *ti, struct request *clone,
			    blk_status_t error, union map_info *map_context)
{
	struct dm_mpath_io *mpio = get_mpio(map_context);
	struct pgpath *pgpath = mpio->pgpath;
	int r = DM_ENDIO_DONE;

	/*
	 * We don't queue any clone request inside the multipath target
	 * during end I/O handling, since those clone requests don't have
	 * bio clones.  If we queue them inside the multipath target,
	 * we need to make bio clones, that requires memory allocation.
	 * (See drivers/md/dm-rq.c:end_clone_bio() about why the clone requests
	 *  don't have bio clones.)
	 * Instead of queueing the clone request here, we queue the original
	 * request into dm core, which will remake a clone request and
	 * clone bios for it and resubmit it later.
	 */
	if (error && blk_path_error(error)) {
		struct multipath *m = ti->private;

		if (error == BLK_STS_RESOURCE)
			r = DM_ENDIO_DELAY_REQUEUE;
		else
			r = DM_ENDIO_REQUEUE;

		if (pgpath)
			fail_path(pgpath);

		if (atomic_read(&m->nr_valid_paths) == 0 &&
		    !must_push_back_rq(m)) {
			if (error == BLK_STS_IOERR)
				dm_report_EIO(m);
			/* complete with the original error */
			r = DM_ENDIO_DONE;
		}
	}

	if (pgpath) {
		struct path_selector *ps = &pgpath->pg->ps;

		if (ps->type->end_io)
			ps->type->end_io(ps, &pgpath->path, mpio->nr_bytes);
	}

	return r;
}