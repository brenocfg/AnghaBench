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
struct loop_device {scalar_t__ lo_state; int use_dio; int lo_flags; int old_gfp_mask; int /*<<< orphan*/  lo_disk; int /*<<< orphan*/  lo_queue; scalar_t__ lo_sizelimit; int /*<<< orphan*/ * ioctl; int /*<<< orphan*/ * transfer; struct file* lo_backing_file; struct block_device* lo_device; } ;
struct inode {int /*<<< orphan*/  i_bdev; int /*<<< orphan*/  i_mode; } ;
struct file {int f_mode; TYPE_1__* f_op; struct address_space* f_mapping; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ sector_t ;
typedef  int loff_t ;
typedef  int fmode_t ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {scalar_t__ fsync; int /*<<< orphan*/  write_iter; } ;

/* Variables and functions */
 int EBADF ; 
 int EBUSY ; 
 int EFBIG ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int LO_FLAGS_PARTSCAN ; 
 int LO_FLAGS_READ_ONLY ; 
 scalar_t__ Lo_bound ; 
 scalar_t__ Lo_unbound ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int __GFP_FS ; 
 int __GFP_IO ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_set_size (struct block_device*,int) ; 
 int /*<<< orphan*/  bdgrab (struct block_device*) ; 
 int /*<<< orphan*/  blk_queue_write_cache (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  block_size (int /*<<< orphan*/ ) ; 
 TYPE_2__* disk_to_dev (int /*<<< orphan*/ ) ; 
 struct file* fget (unsigned int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int get_loop_size (struct loop_device*,struct file*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_ctl_mutex ; 
 int loop_prepare_queue (struct loop_device*) ; 
 int /*<<< orphan*/  loop_reread_partitions (struct loop_device*,struct block_device*) ; 
 int /*<<< orphan*/  loop_sysfs_init (struct loop_device*) ; 
 int /*<<< orphan*/  loop_update_dio (struct loop_device*) ; 
 int loop_validate_file (struct file*,struct block_device*) ; 
 int mapping_gfp_mask (struct address_space*) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (struct address_space*,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ part_shift ; 
 int /*<<< orphan*/  set_blocksize (struct block_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_device_ro (struct block_device*,int) ; 

__attribute__((used)) static int loop_set_fd(struct loop_device *lo, fmode_t mode,
		       struct block_device *bdev, unsigned int arg)
{
	struct file	*file;
	struct inode	*inode;
	struct address_space *mapping;
	int		lo_flags = 0;
	int		error;
	loff_t		size;
	bool		partscan;

	/* This is safe, since we have a reference from open(). */
	__module_get(THIS_MODULE);

	error = -EBADF;
	file = fget(arg);
	if (!file)
		goto out;

	error = mutex_lock_killable(&loop_ctl_mutex);
	if (error)
		goto out_putf;

	error = -EBUSY;
	if (lo->lo_state != Lo_unbound)
		goto out_unlock;

	error = loop_validate_file(file, bdev);
	if (error)
		goto out_unlock;

	mapping = file->f_mapping;
	inode = mapping->host;

	if (!(file->f_mode & FMODE_WRITE) || !(mode & FMODE_WRITE) ||
	    !file->f_op->write_iter)
		lo_flags |= LO_FLAGS_READ_ONLY;

	error = -EFBIG;
	size = get_loop_size(lo, file);
	if ((loff_t)(sector_t)size != size)
		goto out_unlock;
	error = loop_prepare_queue(lo);
	if (error)
		goto out_unlock;

	error = 0;

	set_device_ro(bdev, (lo_flags & LO_FLAGS_READ_ONLY) != 0);

	lo->use_dio = false;
	lo->lo_device = bdev;
	lo->lo_flags = lo_flags;
	lo->lo_backing_file = file;
	lo->transfer = NULL;
	lo->ioctl = NULL;
	lo->lo_sizelimit = 0;
	lo->old_gfp_mask = mapping_gfp_mask(mapping);
	mapping_set_gfp_mask(mapping, lo->old_gfp_mask & ~(__GFP_IO|__GFP_FS));

	if (!(lo_flags & LO_FLAGS_READ_ONLY) && file->f_op->fsync)
		blk_queue_write_cache(lo->lo_queue, true, false);

	loop_update_dio(lo);
	set_capacity(lo->lo_disk, size);
	bd_set_size(bdev, size << 9);
	loop_sysfs_init(lo);
	/* let user-space know about the new size */
	kobject_uevent(&disk_to_dev(bdev->bd_disk)->kobj, KOBJ_CHANGE);

	set_blocksize(bdev, S_ISBLK(inode->i_mode) ?
		      block_size(inode->i_bdev) : PAGE_SIZE);

	lo->lo_state = Lo_bound;
	if (part_shift)
		lo->lo_flags |= LO_FLAGS_PARTSCAN;
	partscan = lo->lo_flags & LO_FLAGS_PARTSCAN;

	/* Grab the block_device to prevent its destruction after we
	 * put /dev/loopXX inode. Later in __loop_clr_fd() we bdput(bdev).
	 */
	bdgrab(bdev);
	mutex_unlock(&loop_ctl_mutex);
	if (partscan)
		loop_reread_partitions(lo, bdev);
	return 0;

out_unlock:
	mutex_unlock(&loop_ctl_mutex);
out_putf:
	fput(file);
out:
	/* This is safe: open() is still holding a reference. */
	module_put(THIS_MODULE);
	return error;
}