#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dmz_metadata {TYPE_3__* dev; TYPE_1__* sb; } ;
struct dmz_mblock {int /*<<< orphan*/  page; int /*<<< orphan*/  state; scalar_t__ no; } ;
struct TYPE_5__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_end_io; struct dmz_mblock* bi_private; TYPE_2__ bi_iter; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_4__ {scalar_t__ block; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_BLOCK_SIZE ; 
 int /*<<< orphan*/  DMZ_META_ERROR ; 
 int /*<<< orphan*/  DMZ_META_WRITING ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_PRIO ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dmz_bdev_is_dying (TYPE_3__*) ; 
 int /*<<< orphan*/  dmz_blk2sect (scalar_t__) ; 
 int /*<<< orphan*/  dmz_mblock_bio_end_io ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static int dmz_write_mblock(struct dmz_metadata *zmd, struct dmz_mblock *mblk,
			    unsigned int set)
{
	sector_t block = zmd->sb[set].block + mblk->no;
	struct bio *bio;

	if (dmz_bdev_is_dying(zmd->dev))
		return -EIO;

	bio = bio_alloc(GFP_NOIO, 1);
	if (!bio) {
		set_bit(DMZ_META_ERROR, &mblk->state);
		return -ENOMEM;
	}

	set_bit(DMZ_META_WRITING, &mblk->state);

	bio->bi_iter.bi_sector = dmz_blk2sect(block);
	bio_set_dev(bio, zmd->dev->bdev);
	bio->bi_private = mblk;
	bio->bi_end_io = dmz_mblock_bio_end_io;
	bio_set_op_attrs(bio, REQ_OP_WRITE, REQ_META | REQ_PRIO);
	bio_add_page(bio, mblk->page, DMZ_BLOCK_SIZE, 0);
	submit_bio(bio);

	return 0;
}