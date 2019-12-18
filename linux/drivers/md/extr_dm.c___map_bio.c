#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mapped_device {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_3__* bi_disk; TYPE_1__ bi_iter; int /*<<< orphan*/  bi_end_io; } ;
struct dm_target_io {struct dm_target* ti; struct dm_io* io; struct bio clone; } ;
struct dm_target {TYPE_2__* type; } ;
struct dm_io {int /*<<< orphan*/  orig_bio; int /*<<< orphan*/  io_count; struct mapped_device* md; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  blk_qc_t ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
struct TYPE_5__ {int (* map ) (struct dm_target*,struct bio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int /*<<< orphan*/  BLK_STS_DM_REQUEUE ; 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DMWARN (char*,int) ; 
#define  DM_MAPIO_KILL 131 
#define  DM_MAPIO_REMAPPED 130 
#define  DM_MAPIO_REQUEUE 129 
#define  DM_MAPIO_SUBMITTED 128 
 int /*<<< orphan*/  DM_TYPE_NVME_BIO_BASED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clone_endio ; 
 int /*<<< orphan*/  dec_pending (struct dm_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  direct_make_request (struct bio*) ; 
 int /*<<< orphan*/  free_tio (struct dm_target_io*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int stub1 (struct dm_target*,struct bio*) ; 
 int /*<<< orphan*/  trace_block_bio_remap (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_qc_t __map_bio(struct dm_target_io *tio)
{
	int r;
	sector_t sector;
	struct bio *clone = &tio->clone;
	struct dm_io *io = tio->io;
	struct mapped_device *md = io->md;
	struct dm_target *ti = tio->ti;
	blk_qc_t ret = BLK_QC_T_NONE;

	clone->bi_end_io = clone_endio;

	/*
	 * Map the clone.  If r == 0 we don't need to do
	 * anything, the target has assumed ownership of
	 * this io.
	 */
	atomic_inc(&io->io_count);
	sector = clone->bi_iter.bi_sector;

	r = ti->type->map(ti, clone);
	switch (r) {
	case DM_MAPIO_SUBMITTED:
		break;
	case DM_MAPIO_REMAPPED:
		/* the bio has been remapped so dispatch it */
		trace_block_bio_remap(clone->bi_disk->queue, clone,
				      bio_dev(io->orig_bio), sector);
		if (md->type == DM_TYPE_NVME_BIO_BASED)
			ret = direct_make_request(clone);
		else
			ret = generic_make_request(clone);
		break;
	case DM_MAPIO_KILL:
		free_tio(tio);
		dec_pending(io, BLK_STS_IOERR);
		break;
	case DM_MAPIO_REQUEUE:
		free_tio(tio);
		dec_pending(io, BLK_STS_DM_REQUEUE);
		break;
	default:
		DMWARN("unimplemented target map return value: %d", r);
		BUG();
	}

	return ret;
}