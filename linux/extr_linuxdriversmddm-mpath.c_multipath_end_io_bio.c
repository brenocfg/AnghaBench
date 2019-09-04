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
struct pgpath {int /*<<< orphan*/  path; TYPE_1__* pg; } ;
struct path_selector {TYPE_2__* type; } ;
struct multipath {int /*<<< orphan*/  process_queued_bios; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  queued_bios; int /*<<< orphan*/  nr_valid_paths; } ;
struct dm_target {struct multipath* private; } ;
struct dm_mpath_io {int /*<<< orphan*/  nr_bytes; struct pgpath* pgpath; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* end_io ) (struct path_selector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct path_selector ps; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_IOERR ; 
 int DM_ENDIO_DONE ; 
 int DM_ENDIO_INCOMPLETE ; 
 int DM_ENDIO_REQUEUE ; 
 int /*<<< orphan*/  MPATHF_QUEUE_IF_NO_PATH ; 
 int /*<<< orphan*/  MPATHF_QUEUE_IO ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  blk_path_error (scalar_t__) ; 
 int /*<<< orphan*/  dm_report_EIO (struct multipath*) ; 
 int /*<<< orphan*/  fail_path (struct pgpath*) ; 
 struct dm_mpath_io* get_mpio_from_bio (struct bio*) ; 
 int /*<<< orphan*/  kmultipathd ; 
 scalar_t__ must_push_back_bio (struct multipath*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct path_selector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int multipath_end_io_bio(struct dm_target *ti, struct bio *clone,
				blk_status_t *error)
{
	struct multipath *m = ti->private;
	struct dm_mpath_io *mpio = get_mpio_from_bio(clone);
	struct pgpath *pgpath = mpio->pgpath;
	unsigned long flags;
	int r = DM_ENDIO_DONE;

	if (!*error || !blk_path_error(*error))
		goto done;

	if (pgpath)
		fail_path(pgpath);

	if (atomic_read(&m->nr_valid_paths) == 0 &&
	    !test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags)) {
		if (must_push_back_bio(m)) {
			r = DM_ENDIO_REQUEUE;
		} else {
			dm_report_EIO(m);
			*error = BLK_STS_IOERR;
		}
		goto done;
	}

	spin_lock_irqsave(&m->lock, flags);
	bio_list_add(&m->queued_bios, clone);
	spin_unlock_irqrestore(&m->lock, flags);
	if (!test_bit(MPATHF_QUEUE_IO, &m->flags))
		queue_work(kmultipathd, &m->process_queued_bios);

	r = DM_ENDIO_INCOMPLETE;
done:
	if (pgpath) {
		struct path_selector *ps = &pgpath->pg->ps;

		if (ps->type->end_io)
			ps->type->end_io(ps, &pgpath->path, mpio->nr_bytes);
	}

	return r;
}