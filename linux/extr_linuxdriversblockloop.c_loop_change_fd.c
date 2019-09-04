#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct loop_device {scalar_t__ lo_state; int lo_flags; int old_gfp_mask; int /*<<< orphan*/  lo_queue; struct file* lo_backing_file; } ;
struct file {int /*<<< orphan*/  f_mapping; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int ENXIO ; 
 int LO_FLAGS_PARTSCAN ; 
 int LO_FLAGS_READ_ONLY ; 
 scalar_t__ Lo_bound ; 
 int __GFP_FS ; 
 int __GFP_IO ; 
 int /*<<< orphan*/  blk_mq_freeze_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (int /*<<< orphan*/ ) ; 
 struct file* fget (unsigned int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 scalar_t__ get_loop_size (struct loop_device*,struct file*) ; 
 int /*<<< orphan*/  loop_ctl_mutex ; 
 int /*<<< orphan*/  loop_reread_partitions (struct loop_device*,struct block_device*) ; 
 int /*<<< orphan*/  loop_update_dio (struct loop_device*) ; 
 int loop_validate_file (struct file*,struct block_device*) ; 
 int mapping_gfp_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (int /*<<< orphan*/ ,int) ; 
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loop_change_fd(struct loop_device *lo, struct block_device *bdev,
			  unsigned int arg)
{
	struct file	*file = NULL, *old_file;
	int		error;
	bool		partscan;

	error = mutex_lock_killable(&loop_ctl_mutex);
	if (error)
		return error;
	error = -ENXIO;
	if (lo->lo_state != Lo_bound)
		goto out_err;

	/* the loop device has to be read-only */
	error = -EINVAL;
	if (!(lo->lo_flags & LO_FLAGS_READ_ONLY))
		goto out_err;

	error = -EBADF;
	file = fget(arg);
	if (!file)
		goto out_err;

	error = loop_validate_file(file, bdev);
	if (error)
		goto out_err;

	old_file = lo->lo_backing_file;

	error = -EINVAL;

	/* size of the new backing store needs to be the same */
	if (get_loop_size(lo, file) != get_loop_size(lo, old_file))
		goto out_err;

	/* and ... switch */
	blk_mq_freeze_queue(lo->lo_queue);
	mapping_set_gfp_mask(old_file->f_mapping, lo->old_gfp_mask);
	lo->lo_backing_file = file;
	lo->old_gfp_mask = mapping_gfp_mask(file->f_mapping);
	mapping_set_gfp_mask(file->f_mapping,
			     lo->old_gfp_mask & ~(__GFP_IO|__GFP_FS));
	loop_update_dio(lo);
	blk_mq_unfreeze_queue(lo->lo_queue);
	partscan = lo->lo_flags & LO_FLAGS_PARTSCAN;
	mutex_unlock(&loop_ctl_mutex);
	/*
	 * We must drop file reference outside of loop_ctl_mutex as dropping
	 * the file ref can take bd_mutex which creates circular locking
	 * dependency.
	 */
	fput(old_file);
	if (partscan)
		loop_reread_partitions(lo, bdev);
	return 0;

out_err:
	mutex_unlock(&loop_ctl_mutex);
	if (file)
		fput(file);
	return error;
}