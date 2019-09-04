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
struct mirror_set {int /*<<< orphan*/  rh; } ;
struct mirror {int dummy; } ;
struct dm_target {struct mirror_set* private; } ;
struct TYPE_6__ {int /*<<< orphan*/ * bi_disk; } ;
struct dm_raid1_bio_record {struct mirror* m; TYPE_3__ details; int /*<<< orphan*/  write_region; } ;
struct dm_dirty_log {TYPE_1__* type; } ;
struct TYPE_5__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; TYPE_2__ bi_iter; } ;
struct TYPE_4__ {int (* in_sync ) (struct dm_dirty_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int DM_MAPIO_KILL ; 
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 int EWOULDBLOCK ; 
 int REQ_RAHEAD ; 
 int WRITE ; 
 int bio_data_dir (struct bio*) ; 
 struct mirror* choose_mirror (struct mirror_set*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_bio_record (TYPE_3__*,struct bio*) ; 
 struct dm_raid1_bio_record* dm_per_bio_data (struct bio*,int) ; 
 int /*<<< orphan*/  dm_rh_bio_to_region (int /*<<< orphan*/ ,struct bio*) ; 
 struct dm_dirty_log* dm_rh_dirty_log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_bio (struct mirror*,struct bio*) ; 
 int /*<<< orphan*/  queue_bio (struct mirror_set*,struct bio*,int) ; 
 int stub1 (struct dm_dirty_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mirror_map(struct dm_target *ti, struct bio *bio)
{
	int r, rw = bio_data_dir(bio);
	struct mirror *m;
	struct mirror_set *ms = ti->private;
	struct dm_dirty_log *log = dm_rh_dirty_log(ms->rh);
	struct dm_raid1_bio_record *bio_record =
	  dm_per_bio_data(bio, sizeof(struct dm_raid1_bio_record));

	bio_record->details.bi_disk = NULL;

	if (rw == WRITE) {
		/* Save region for mirror_end_io() handler */
		bio_record->write_region = dm_rh_bio_to_region(ms->rh, bio);
		queue_bio(ms, bio, rw);
		return DM_MAPIO_SUBMITTED;
	}

	r = log->type->in_sync(log, dm_rh_bio_to_region(ms->rh, bio), 0);
	if (r < 0 && r != -EWOULDBLOCK)
		return DM_MAPIO_KILL;

	/*
	 * If region is not in-sync queue the bio.
	 */
	if (!r || (r == -EWOULDBLOCK)) {
		if (bio->bi_opf & REQ_RAHEAD)
			return DM_MAPIO_KILL;

		queue_bio(ms, bio, rw);
		return DM_MAPIO_SUBMITTED;
	}

	/*
	 * The region is in-sync and we can perform reads directly.
	 * Store enough information so we can retry if it fails.
	 */
	m = choose_mirror(ms, bio->bi_iter.bi_sector);
	if (unlikely(!m))
		return DM_MAPIO_KILL;

	dm_bio_record(&bio_record->details, bio);
	bio_record->m = m;

	map_bio(m, bio);

	return DM_MAPIO_REMAPPED;
}