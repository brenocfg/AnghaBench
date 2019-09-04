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
struct block_device {int dummy; } ;
struct blk_plug {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int __blkdev_issue_discard (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,struct bio**) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int submit_bio_wait (struct bio*) ; 

int blkdev_issue_discard(struct block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, unsigned long flags)
{
	struct bio *bio = NULL;
	struct blk_plug plug;
	int ret;

	blk_start_plug(&plug);
	ret = __blkdev_issue_discard(bdev, sector, nr_sects, gfp_mask, flags,
			&bio);
	if (!ret && bio) {
		ret = submit_bio_wait(bio);
		if (ret == -EOPNOTSUPP)
			ret = 0;
		bio_put(bio);
	}
	blk_finish_plug(&plug);

	return ret;
}