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
struct TYPE_2__ {scalar_t__ chunksize; } ;
struct mddev {scalar_t__ recovery_cp; scalar_t__ resync_min; int /*<<< orphan*/  recovery; int /*<<< orphan*/  dev_sectors; scalar_t__ bitmap; TYPE_1__ bitmap_info; } ;
struct raid_set {int /*<<< orphan*/  runtime_flags; int /*<<< orphan*/  requested_bitmap_chunk_sectors; struct mddev md; } ;
struct dm_target {struct raid_set* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  DMWARN (char*) ; 
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  MD_RECOVERY_SYNC ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  RT_FLAG_RESHAPE_RS ; 
 int /*<<< orphan*/  RT_FLAG_RS_BITMAP_LOADED ; 
 int /*<<< orphan*/  RT_FLAG_RS_PRERESUMED ; 
 int /*<<< orphan*/  RT_FLAG_UPDATE_SBS ; 
 int __load_dirty_region_bitmap (struct raid_set*) ; 
 int md_bitmap_resize (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mddev_lock_nointr (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 int /*<<< orphan*/  rs_set_rdev_sectors (struct raid_set*) ; 
 int rs_start_reshape (struct raid_set*) ; 
 int /*<<< orphan*/  rs_update_sbs (struct raid_set*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ to_bytes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raid_preresume(struct dm_target *ti)
{
	int r;
	struct raid_set *rs = ti->private;
	struct mddev *mddev = &rs->md;

	/* This is a resume after a suspend of the set -> it's already started. */
	if (test_and_set_bit(RT_FLAG_RS_PRERESUMED, &rs->runtime_flags))
		return 0;

	/*
	 * The superblocks need to be updated on disk if the
	 * array is new or new devices got added (thus zeroed
	 * out by userspace) or __load_dirty_region_bitmap
	 * will overwrite them in core with old data or fail.
	 */
	if (test_bit(RT_FLAG_UPDATE_SBS, &rs->runtime_flags))
		rs_update_sbs(rs);

	/* Load the bitmap from disk unless raid0 */
	r = __load_dirty_region_bitmap(rs);
	if (r)
		return r;

	/* Resize bitmap to adjust to changed region size (aka MD bitmap chunksize) */
	if (test_bit(RT_FLAG_RS_BITMAP_LOADED, &rs->runtime_flags) && mddev->bitmap &&
	    mddev->bitmap_info.chunksize != to_bytes(rs->requested_bitmap_chunk_sectors)) {
		r = md_bitmap_resize(mddev->bitmap, mddev->dev_sectors,
				     to_bytes(rs->requested_bitmap_chunk_sectors), 0);
		if (r)
			DMERR("Failed to resize bitmap");
	}

	/* Check for any resize/reshape on @rs and adjust/initiate */
	/* Be prepared for mddev_resume() in raid_resume() */
	set_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
	if (mddev->recovery_cp && mddev->recovery_cp < MaxSector) {
		set_bit(MD_RECOVERY_SYNC, &mddev->recovery);
		mddev->resync_min = mddev->recovery_cp;
	}

	/* Check for any reshape request unless new raid set */
	if (test_bit(RT_FLAG_RESHAPE_RS, &rs->runtime_flags)) {
		/* Initiate a reshape. */
		rs_set_rdev_sectors(rs);
		mddev_lock_nointr(mddev);
		r = rs_start_reshape(rs);
		mddev_unlock(mddev);
		if (r)
			DMWARN("Failed to check/start reshape, continuing without change");
		r = 0;
	}

	return r;
}