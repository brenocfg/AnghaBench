#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ offset; scalar_t__ default_offset; scalar_t__ nodes; int /*<<< orphan*/  default_space; int /*<<< orphan*/  space; } ;
struct mddev {scalar_t__ major_version; scalar_t__ minor_version; scalar_t__ ctime; scalar_t__ level; int persistent; scalar_t__ chunk_sectors; int dev_sectors; scalar_t__ raid_disks; scalar_t__ layout; scalar_t__ new_layout; TYPE_3__ bitmap_info; struct bitmap* bitmap; scalar_t__ sync_thread; scalar_t__ recovery; int /*<<< orphan*/ * thread; TYPE_1__* pers; } ;
struct TYPE_8__ {scalar_t__ file; } ;
struct bitmap {TYPE_2__ storage; } ;
typedef  int sector_t ;
struct TYPE_10__ {scalar_t__ major_version; scalar_t__ minor_version; scalar_t__ ctime; scalar_t__ level; scalar_t__ chunk_size; int state; int size; scalar_t__ raid_disks; scalar_t__ layout; int /*<<< orphan*/  not_persistent; } ;
typedef  TYPE_4__ mdu_array_info_t ;
struct TYPE_11__ {scalar_t__ (* lock_all_bitmaps ) (struct mddev*) ;int /*<<< orphan*/  (* leave ) (struct mddev*) ;int /*<<< orphan*/  (* unlock_all_bitmaps ) (struct mddev*) ;} ;
struct TYPE_7__ {int (* check_reshape ) (struct mddev*) ;int /*<<< orphan*/ * quiesce; } ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  IS_ERR (struct bitmap*) ; 
 int MD_SB_BITMAP_PRESENT ; 
 int PTR_ERR (struct bitmap*) ; 
 struct bitmap* md_bitmap_create (struct mddev*,int) ; 
 int /*<<< orphan*/  md_bitmap_destroy (struct mddev*) ; 
 int md_bitmap_load (struct mddev*) ; 
 TYPE_6__* md_cluster_ops ; 
 int /*<<< orphan*/  md_update_sb (struct mddev*,int) ; 
 int /*<<< orphan*/  mddev_resume (struct mddev*) ; 
 int /*<<< orphan*/  mddev_suspend (struct mddev*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int stub1 (struct mddev*) ; 
 scalar_t__ stub2 (struct mddev*) ; 
 int /*<<< orphan*/  stub3 (struct mddev*) ; 
 int /*<<< orphan*/  stub4 (struct mddev*) ; 
 int update_raid_disks (struct mddev*,scalar_t__) ; 
 int update_size (struct mddev*,int) ; 

__attribute__((used)) static int update_array_info(struct mddev *mddev, mdu_array_info_t *info)
{
	int rv = 0;
	int cnt = 0;
	int state = 0;

	/* calculate expected state,ignoring low bits */
	if (mddev->bitmap && mddev->bitmap_info.offset)
		state |= (1 << MD_SB_BITMAP_PRESENT);

	if (mddev->major_version != info->major_version ||
	    mddev->minor_version != info->minor_version ||
/*	    mddev->patch_version != info->patch_version || */
	    mddev->ctime         != info->ctime         ||
	    mddev->level         != info->level         ||
/*	    mddev->layout        != info->layout        || */
	    mddev->persistent	 != !info->not_persistent ||
	    mddev->chunk_sectors != info->chunk_size >> 9 ||
	    /* ignore bottom 8 bits of state, and allow SB_BITMAP_PRESENT to change */
	    ((state^info->state) & 0xfffffe00)
		)
		return -EINVAL;
	/* Check there is only one change */
	if (info->size >= 0 && mddev->dev_sectors / 2 != info->size)
		cnt++;
	if (mddev->raid_disks != info->raid_disks)
		cnt++;
	if (mddev->layout != info->layout)
		cnt++;
	if ((state ^ info->state) & (1<<MD_SB_BITMAP_PRESENT))
		cnt++;
	if (cnt == 0)
		return 0;
	if (cnt > 1)
		return -EINVAL;

	if (mddev->layout != info->layout) {
		/* Change layout
		 * we don't need to do anything at the md level, the
		 * personality will take care of it all.
		 */
		if (mddev->pers->check_reshape == NULL)
			return -EINVAL;
		else {
			mddev->new_layout = info->layout;
			rv = mddev->pers->check_reshape(mddev);
			if (rv)
				mddev->new_layout = mddev->layout;
			return rv;
		}
	}
	if (info->size >= 0 && mddev->dev_sectors / 2 != info->size)
		rv = update_size(mddev, (sector_t)info->size * 2);

	if (mddev->raid_disks    != info->raid_disks)
		rv = update_raid_disks(mddev, info->raid_disks);

	if ((state ^ info->state) & (1<<MD_SB_BITMAP_PRESENT)) {
		if (mddev->pers->quiesce == NULL || mddev->thread == NULL) {
			rv = -EINVAL;
			goto err;
		}
		if (mddev->recovery || mddev->sync_thread) {
			rv = -EBUSY;
			goto err;
		}
		if (info->state & (1<<MD_SB_BITMAP_PRESENT)) {
			struct bitmap *bitmap;
			/* add the bitmap */
			if (mddev->bitmap) {
				rv = -EEXIST;
				goto err;
			}
			if (mddev->bitmap_info.default_offset == 0) {
				rv = -EINVAL;
				goto err;
			}
			mddev->bitmap_info.offset =
				mddev->bitmap_info.default_offset;
			mddev->bitmap_info.space =
				mddev->bitmap_info.default_space;
			bitmap = md_bitmap_create(mddev, -1);
			mddev_suspend(mddev);
			if (!IS_ERR(bitmap)) {
				mddev->bitmap = bitmap;
				rv = md_bitmap_load(mddev);
			} else
				rv = PTR_ERR(bitmap);
			if (rv)
				md_bitmap_destroy(mddev);
			mddev_resume(mddev);
		} else {
			/* remove the bitmap */
			if (!mddev->bitmap) {
				rv = -ENOENT;
				goto err;
			}
			if (mddev->bitmap->storage.file) {
				rv = -EINVAL;
				goto err;
			}
			if (mddev->bitmap_info.nodes) {
				/* hold PW on all the bitmap lock */
				if (md_cluster_ops->lock_all_bitmaps(mddev) <= 0) {
					pr_warn("md: can't change bitmap to none since the array is in use by more than one node\n");
					rv = -EPERM;
					md_cluster_ops->unlock_all_bitmaps(mddev);
					goto err;
				}

				mddev->bitmap_info.nodes = 0;
				md_cluster_ops->leave(mddev);
			}
			mddev_suspend(mddev);
			md_bitmap_destroy(mddev);
			mddev_resume(mddev);
			mddev->bitmap_info.offset = 0;
		}
	}
	md_update_sb(mddev, 1);
	return rv;
err:
	return rv;
}