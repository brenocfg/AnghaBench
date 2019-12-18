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
struct page {int dummy; } ;
struct dmz_metadata {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_BLOCK_SIZE ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int REQ_META ; 
 int REQ_PRIO ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int,int) ; 
 scalar_t__ dmz_bdev_is_dying (TYPE_2__*) ; 
 int /*<<< orphan*/  dmz_blk2sect (int /*<<< orphan*/ ) ; 
 int submit_bio_wait (struct bio*) ; 

__attribute__((used)) static int dmz_rdwr_block(struct dmz_metadata *zmd, int op, sector_t block,
			  struct page *page)
{
	struct bio *bio;
	int ret;

	if (dmz_bdev_is_dying(zmd->dev))
		return -EIO;

	bio = bio_alloc(GFP_NOIO, 1);
	if (!bio)
		return -ENOMEM;

	bio->bi_iter.bi_sector = dmz_blk2sect(block);
	bio_set_dev(bio, zmd->dev->bdev);
	bio_set_op_attrs(bio, op, REQ_SYNC | REQ_META | REQ_PRIO);
	bio_add_page(bio, page, DMZ_BLOCK_SIZE, 0);
	ret = submit_bio_wait(bio);
	bio_put(bio);

	return ret;
}