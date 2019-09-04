#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ daemon_sleep; int /*<<< orphan*/  chunksize; int /*<<< orphan*/  external; scalar_t__ offset; struct file* file; } ;
struct TYPE_5__ {struct kernfs_node* sd; } ;
struct mddev {TYPE_3__ bitmap_info; int /*<<< orphan*/  flags; TYPE_1__ kobj; int /*<<< orphan*/  resync_max_sectors; } ;
struct kernfs_node {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  pages; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {struct file* file; } ;
struct bitmap {int cluster_slot; int /*<<< orphan*/  flags; TYPE_4__ counts; int /*<<< orphan*/  daemon_lastrun; TYPE_2__ storage; int /*<<< orphan*/ * sysfs_can_clear; struct mddev* mddev; int /*<<< orphan*/  behind_wait; int /*<<< orphan*/  overflow_wait; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  pending_writes; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  bitmap_super_t ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_WRITE_ERROR ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 struct bitmap* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MD_ARRAY_FIRST_USE ; 
 int /*<<< orphan*/  MD_HAS_JOURNAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bmname (struct bitmap*) ; 
 int /*<<< orphan*/  get_file (struct file*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct bitmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_bitmap_free (struct bitmap*) ; 
 int md_bitmap_new_disk_sb (struct bitmap*) ; 
 int md_bitmap_read_sb (struct bitmap*) ; 
 int md_bitmap_resize (struct bitmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* sysfs_get_dirent (struct kernfs_node*,char*) ; 
 int /*<<< orphan*/  sysfs_put (struct kernfs_node*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_fsync (struct file*,int) ; 

struct bitmap *md_bitmap_create(struct mddev *mddev, int slot)
{
	struct bitmap *bitmap;
	sector_t blocks = mddev->resync_max_sectors;
	struct file *file = mddev->bitmap_info.file;
	int err;
	struct kernfs_node *bm = NULL;

	BUILD_BUG_ON(sizeof(bitmap_super_t) != 256);

	BUG_ON(file && mddev->bitmap_info.offset);

	if (test_bit(MD_HAS_JOURNAL, &mddev->flags)) {
		pr_notice("md/raid:%s: array with journal cannot have bitmap\n",
			  mdname(mddev));
		return ERR_PTR(-EBUSY);
	}

	bitmap = kzalloc(sizeof(*bitmap), GFP_KERNEL);
	if (!bitmap)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&bitmap->counts.lock);
	atomic_set(&bitmap->pending_writes, 0);
	init_waitqueue_head(&bitmap->write_wait);
	init_waitqueue_head(&bitmap->overflow_wait);
	init_waitqueue_head(&bitmap->behind_wait);

	bitmap->mddev = mddev;
	bitmap->cluster_slot = slot;

	if (mddev->kobj.sd)
		bm = sysfs_get_dirent(mddev->kobj.sd, "bitmap");
	if (bm) {
		bitmap->sysfs_can_clear = sysfs_get_dirent(bm, "can_clear");
		sysfs_put(bm);
	} else
		bitmap->sysfs_can_clear = NULL;

	bitmap->storage.file = file;
	if (file) {
		get_file(file);
		/* As future accesses to this file will use bmap,
		 * and bypass the page cache, we must sync the file
		 * first.
		 */
		vfs_fsync(file, 1);
	}
	/* read superblock from bitmap file (this sets mddev->bitmap_info.chunksize) */
	if (!mddev->bitmap_info.external) {
		/*
		 * If 'MD_ARRAY_FIRST_USE' is set, then device-mapper is
		 * instructing us to create a new on-disk bitmap instance.
		 */
		if (test_and_clear_bit(MD_ARRAY_FIRST_USE, &mddev->flags))
			err = md_bitmap_new_disk_sb(bitmap);
		else
			err = md_bitmap_read_sb(bitmap);
	} else {
		err = 0;
		if (mddev->bitmap_info.chunksize == 0 ||
		    mddev->bitmap_info.daemon_sleep == 0)
			/* chunksize and time_base need to be
			 * set first. */
			err = -EINVAL;
	}
	if (err)
		goto error;

	bitmap->daemon_lastrun = jiffies;
	err = md_bitmap_resize(bitmap, blocks, mddev->bitmap_info.chunksize, 1);
	if (err)
		goto error;

	pr_debug("created bitmap (%lu pages) for device %s\n",
		 bitmap->counts.pages, bmname(bitmap));

	err = test_bit(BITMAP_WRITE_ERROR, &bitmap->flags) ? -EIO : 0;
	if (err)
		goto error;

	return bitmap;
 error:
	md_bitmap_free(bitmap);
	return ERR_PTR(err);
}