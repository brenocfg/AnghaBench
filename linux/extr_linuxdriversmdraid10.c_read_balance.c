#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct geom {int near_copies; int far_copies; } ;
struct r10conf {scalar_t__ const next_resync; int copies; TYPE_2__* mirrors; TYPE_3__* mddev; struct geom geo; } ;
struct r10bio {scalar_t__ sector; int sectors; int read_slot; TYPE_1__* devs; int /*<<< orphan*/  state; } ;
struct md_rdev {scalar_t__ recovery_offset; int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_9__ {scalar_t__ (* area_resyncing ) (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__ const,scalar_t__ const) ;} ;
struct TYPE_8__ {scalar_t__ recovery_cp; } ;
struct TYPE_7__ {scalar_t__ head_position; int /*<<< orphan*/  rdev; int /*<<< orphan*/  replacement; } ;
struct TYPE_6__ {scalar_t__ bio; int devnum; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 scalar_t__ IO_BLOCKED ; 
 int /*<<< orphan*/  In_sync ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  R10BIO_FailFast ; 
 int /*<<< orphan*/  READ ; 
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_badblock (struct md_rdev*,scalar_t__,int,scalar_t__*,int*) ; 
 TYPE_5__* md_cluster_ops ; 
 scalar_t__ mddev_is_clustered (TYPE_3__*) ; 
 int /*<<< orphan*/  raid10_find_phys (struct r10conf*,struct r10bio*) ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__ const,scalar_t__ const) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct md_rdev *read_balance(struct r10conf *conf,
				    struct r10bio *r10_bio,
				    int *max_sectors)
{
	const sector_t this_sector = r10_bio->sector;
	int disk, slot;
	int sectors = r10_bio->sectors;
	int best_good_sectors;
	sector_t new_distance, best_dist;
	struct md_rdev *best_rdev, *rdev = NULL;
	int do_balance;
	int best_slot;
	struct geom *geo = &conf->geo;

	raid10_find_phys(conf, r10_bio);
	rcu_read_lock();
	best_slot = -1;
	best_rdev = NULL;
	best_dist = MaxSector;
	best_good_sectors = 0;
	do_balance = 1;
	clear_bit(R10BIO_FailFast, &r10_bio->state);
	/*
	 * Check if we can balance. We can balance on the whole
	 * device if no resync is going on (recovery is ok), or below
	 * the resync window. We take the first readable disk when
	 * above the resync window.
	 */
	if ((conf->mddev->recovery_cp < MaxSector
	     && (this_sector + sectors >= conf->next_resync)) ||
	    (mddev_is_clustered(conf->mddev) &&
	     md_cluster_ops->area_resyncing(conf->mddev, READ, this_sector,
					    this_sector + sectors)))
		do_balance = 0;

	for (slot = 0; slot < conf->copies ; slot++) {
		sector_t first_bad;
		int bad_sectors;
		sector_t dev_sector;

		if (r10_bio->devs[slot].bio == IO_BLOCKED)
			continue;
		disk = r10_bio->devs[slot].devnum;
		rdev = rcu_dereference(conf->mirrors[disk].replacement);
		if (rdev == NULL || test_bit(Faulty, &rdev->flags) ||
		    r10_bio->devs[slot].addr + sectors > rdev->recovery_offset)
			rdev = rcu_dereference(conf->mirrors[disk].rdev);
		if (rdev == NULL ||
		    test_bit(Faulty, &rdev->flags))
			continue;
		if (!test_bit(In_sync, &rdev->flags) &&
		    r10_bio->devs[slot].addr + sectors > rdev->recovery_offset)
			continue;

		dev_sector = r10_bio->devs[slot].addr;
		if (is_badblock(rdev, dev_sector, sectors,
				&first_bad, &bad_sectors)) {
			if (best_dist < MaxSector)
				/* Already have a better slot */
				continue;
			if (first_bad <= dev_sector) {
				/* Cannot read here.  If this is the
				 * 'primary' device, then we must not read
				 * beyond 'bad_sectors' from another device.
				 */
				bad_sectors -= (dev_sector - first_bad);
				if (!do_balance && sectors > bad_sectors)
					sectors = bad_sectors;
				if (best_good_sectors > sectors)
					best_good_sectors = sectors;
			} else {
				sector_t good_sectors =
					first_bad - dev_sector;
				if (good_sectors > best_good_sectors) {
					best_good_sectors = good_sectors;
					best_slot = slot;
					best_rdev = rdev;
				}
				if (!do_balance)
					/* Must read from here */
					break;
			}
			continue;
		} else
			best_good_sectors = sectors;

		if (!do_balance)
			break;

		if (best_slot >= 0)
			/* At least 2 disks to choose from so failfast is OK */
			set_bit(R10BIO_FailFast, &r10_bio->state);
		/* This optimisation is debatable, and completely destroys
		 * sequential read speed for 'far copies' arrays.  So only
		 * keep it for 'near' arrays, and review those later.
		 */
		if (geo->near_copies > 1 && !atomic_read(&rdev->nr_pending))
			new_distance = 0;

		/* for far > 1 always use the lowest address */
		else if (geo->far_copies > 1)
			new_distance = r10_bio->devs[slot].addr;
		else
			new_distance = abs(r10_bio->devs[slot].addr -
					   conf->mirrors[disk].head_position);
		if (new_distance < best_dist) {
			best_dist = new_distance;
			best_slot = slot;
			best_rdev = rdev;
		}
	}
	if (slot >= conf->copies) {
		slot = best_slot;
		rdev = best_rdev;
	}

	if (slot >= 0) {
		atomic_inc(&rdev->nr_pending);
		r10_bio->read_slot = slot;
	} else
		rdev = NULL;
	rcu_read_unlock();
	*max_sectors = best_good_sectors;

	return rdev;
}