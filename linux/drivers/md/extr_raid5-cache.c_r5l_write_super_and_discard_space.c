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
struct r5l_log {scalar_t__ last_checkpoint; scalar_t__ device_size; TYPE_1__* rdev; } ;
struct mddev {int /*<<< orphan*/  sb_flags; } ;
struct block_device {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {scalar_t__ data_offset; struct mddev* mddev; struct block_device* bdev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 int /*<<< orphan*/  MD_SB_CHANGE_PENDING ; 
 int /*<<< orphan*/  bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  blk_queue_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkdev_issue_discard (struct block_device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_update_sb (struct mddev*,int) ; 
 int /*<<< orphan*/  mddev_trylock (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 int /*<<< orphan*/  r5l_write_super (struct r5l_log*,scalar_t__) ; 
 int /*<<< orphan*/  set_mask_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void r5l_write_super_and_discard_space(struct r5l_log *log,
	sector_t end)
{
	struct block_device *bdev = log->rdev->bdev;
	struct mddev *mddev;

	r5l_write_super(log, end);

	if (!blk_queue_discard(bdev_get_queue(bdev)))
		return;

	mddev = log->rdev->mddev;
	/*
	 * Discard could zero data, so before discard we must make sure
	 * superblock is updated to new log tail. Updating superblock (either
	 * directly call md_update_sb() or depend on md thread) must hold
	 * reconfig mutex. On the other hand, raid5_quiesce is called with
	 * reconfig_mutex hold. The first step of raid5_quiesce() is waitting
	 * for all IO finish, hence waitting for reclaim thread, while reclaim
	 * thread is calling this function and waitting for reconfig mutex. So
	 * there is a deadlock. We workaround this issue with a trylock.
	 * FIXME: we could miss discard if we can't take reconfig mutex
	 */
	set_mask_bits(&mddev->sb_flags, 0,
		BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
	if (!mddev_trylock(mddev))
		return;
	md_update_sb(mddev, 1);
	mddev_unlock(mddev);

	/* discard IO error really doesn't matter, ignore it */
	if (log->last_checkpoint < end) {
		blkdev_issue_discard(bdev,
				log->last_checkpoint + log->rdev->data_offset,
				end - log->last_checkpoint, GFP_NOIO, 0);
	} else {
		blkdev_issue_discard(bdev,
				log->last_checkpoint + log->rdev->data_offset,
				log->device_size - log->last_checkpoint,
				GFP_NOIO, 0);
		blkdev_issue_discard(bdev, log->rdev->data_offset, end,
				GFP_NOIO, 0);
	}
}