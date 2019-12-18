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
struct dmz_metadata {size_t mblk_primary; TYPE_3__* dev; int /*<<< orphan*/  mblk_lock; TYPE_1__* sb; } ;
struct dmz_mblock {int /*<<< orphan*/  page; int /*<<< orphan*/  state; int /*<<< orphan*/  ref; } ;
struct TYPE_5__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_end_io; struct dmz_mblock* bi_private; TYPE_2__ bi_iter; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_4__ {scalar_t__ block; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_BLOCK_SIZE ; 
 int /*<<< orphan*/  DMZ_META_READING ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dmz_mblock* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int REQ_PRIO ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int) ; 
 struct dmz_mblock* dmz_alloc_mblock (struct dmz_metadata*,scalar_t__) ; 
 scalar_t__ dmz_bdev_is_dying (TYPE_3__*) ; 
 int /*<<< orphan*/  dmz_blk2sect (scalar_t__) ; 
 int /*<<< orphan*/  dmz_free_mblock (struct dmz_metadata*,struct dmz_mblock*) ; 
 struct dmz_mblock* dmz_get_mblock_fast (struct dmz_metadata*,scalar_t__) ; 
 int /*<<< orphan*/  dmz_insert_mblock (struct dmz_metadata*,struct dmz_mblock*) ; 
 int /*<<< orphan*/  dmz_mblock_bio_end_io ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static struct dmz_mblock *dmz_get_mblock_slow(struct dmz_metadata *zmd,
					      sector_t mblk_no)
{
	struct dmz_mblock *mblk, *m;
	sector_t block = zmd->sb[zmd->mblk_primary].block + mblk_no;
	struct bio *bio;

	if (dmz_bdev_is_dying(zmd->dev))
		return ERR_PTR(-EIO);

	/* Get a new block and a BIO to read it */
	mblk = dmz_alloc_mblock(zmd, mblk_no);
	if (!mblk)
		return ERR_PTR(-ENOMEM);

	bio = bio_alloc(GFP_NOIO, 1);
	if (!bio) {
		dmz_free_mblock(zmd, mblk);
		return ERR_PTR(-ENOMEM);
	}

	spin_lock(&zmd->mblk_lock);

	/*
	 * Make sure that another context did not start reading
	 * the block already.
	 */
	m = dmz_get_mblock_fast(zmd, mblk_no);
	if (m) {
		spin_unlock(&zmd->mblk_lock);
		dmz_free_mblock(zmd, mblk);
		bio_put(bio);
		return m;
	}

	mblk->ref++;
	set_bit(DMZ_META_READING, &mblk->state);
	dmz_insert_mblock(zmd, mblk);

	spin_unlock(&zmd->mblk_lock);

	/* Submit read BIO */
	bio->bi_iter.bi_sector = dmz_blk2sect(block);
	bio_set_dev(bio, zmd->dev->bdev);
	bio->bi_private = mblk;
	bio->bi_end_io = dmz_mblock_bio_end_io;
	bio_set_op_attrs(bio, REQ_OP_READ, REQ_META | REQ_PRIO);
	bio_add_page(bio, mblk->page, DMZ_BLOCK_SIZE, 0);
	submit_bio(bio);

	return mblk;
}