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
struct dm_target {struct clone* private; } ;
struct clone {int /*<<< orphan*/  cmd; int /*<<< orphan*/  ios_in_flight; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 scalar_t__ CM_FAIL ; 
 int DM_MAPIO_KILL ; 
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 scalar_t__ READ ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 unsigned long bio_to_region (struct clone*,struct bio*) ; 
 scalar_t__ dm_clone_is_region_hydrated (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dm_target_offset (struct dm_target*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_clone_mode (struct clone*) ; 
 int /*<<< orphan*/  hydrate_bio_region (struct clone*,struct bio*) ; 
 int /*<<< orphan*/  process_discard_bio (struct clone*,struct bio*) ; 
 int /*<<< orphan*/  remap_and_issue (struct clone*,struct bio*) ; 
 int /*<<< orphan*/  remap_to_dest (struct clone*,struct bio*) ; 
 int /*<<< orphan*/  remap_to_source (struct clone*,struct bio*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int clone_map(struct dm_target *ti, struct bio *bio)
{
	struct clone *clone = ti->private;
	unsigned long region_nr;

	atomic_inc(&clone->ios_in_flight);

	if (unlikely(get_clone_mode(clone) == CM_FAIL))
		return DM_MAPIO_KILL;

	/*
	 * REQ_PREFLUSH bios carry no data:
	 *
	 * - Commit metadata, if changed
	 *
	 * - Pass down to destination device
	 */
	if (bio->bi_opf & REQ_PREFLUSH) {
		remap_and_issue(clone, bio);
		return DM_MAPIO_SUBMITTED;
	}

	bio->bi_iter.bi_sector = dm_target_offset(ti, bio->bi_iter.bi_sector);

	/*
	 * dm-clone interprets discards and performs a fast hydration of the
	 * discarded regions, i.e., we skip the copy from the source device and
	 * just mark the regions as hydrated.
	 */
	if (bio_op(bio) == REQ_OP_DISCARD) {
		process_discard_bio(clone, bio);
		return DM_MAPIO_SUBMITTED;
	}

	/*
	 * If the bio's region is hydrated, redirect it to the destination
	 * device.
	 *
	 * If the region is not hydrated and the bio is a READ, redirect it to
	 * the source device.
	 *
	 * Else, defer WRITE bio until after its region has been hydrated and
	 * start the region's hydration immediately.
	 */
	region_nr = bio_to_region(clone, bio);
	if (dm_clone_is_region_hydrated(clone->cmd, region_nr)) {
		remap_and_issue(clone, bio);
		return DM_MAPIO_SUBMITTED;
	} else if (bio_data_dir(bio) == READ) {
		remap_to_source(clone, bio);
		return DM_MAPIO_REMAPPED;
	}

	remap_to_dest(clone, bio);
	hydrate_bio_region(clone, bio);

	return DM_MAPIO_SUBMITTED;
}