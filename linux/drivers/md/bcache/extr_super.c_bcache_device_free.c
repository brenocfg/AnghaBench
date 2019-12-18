#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bcache_device {int /*<<< orphan*/  cl; int /*<<< orphan*/  stripe_sectors_dirty; int /*<<< orphan*/  full_dirty_stripes; int /*<<< orphan*/  bio_split; TYPE_1__* disk; scalar_t__ c; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  first_minor; scalar_t__ queue; int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int GENHD_FL_UP ; 
 int /*<<< orphan*/  bcache_device_detach (struct bcache_device*) ; 
 int /*<<< orphan*/  bcache_device_idx ; 
 int /*<<< orphan*/  bch_register_lock ; 
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 int /*<<< orphan*/  closure_debug_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  first_minor_to_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 

__attribute__((used)) static void bcache_device_free(struct bcache_device *d)
{
	lockdep_assert_held(&bch_register_lock);

	pr_info("%s stopped", d->disk->disk_name);

	if (d->c)
		bcache_device_detach(d);
	if (d->disk && d->disk->flags & GENHD_FL_UP)
		del_gendisk(d->disk);
	if (d->disk && d->disk->queue)
		blk_cleanup_queue(d->disk->queue);
	if (d->disk) {
		ida_simple_remove(&bcache_device_idx,
				  first_minor_to_idx(d->disk->first_minor));
		put_disk(d->disk);
	}

	bioset_exit(&d->bio_split);
	kvfree(d->full_dirty_stripes);
	kvfree(d->stripe_sectors_dirty);

	closure_debug_destroy(&d->cl);
}