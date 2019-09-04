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
typedef  int u64 ;
struct rsxx_cardinfo {int /*<<< orphan*/  halt; int /*<<< orphan*/  dma_fault; int /*<<< orphan*/  gendisk; } ;
struct rsxx_bio_meta {int /*<<< orphan*/  pending_dmas; int /*<<< orphan*/  start_time; int /*<<< orphan*/  error; struct bio* bio; } ;
struct request_queue {struct rsxx_cardinfo* queuedata; } ;
struct TYPE_2__ {scalar_t__ bi_size; scalar_t__ bi_sector; } ;
struct bio {scalar_t__ bi_status; TYPE_1__ bi_iter; } ;
typedef  scalar_t__ blk_status_t ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 scalar_t__ BLK_STS_IOERR ; 
 scalar_t__ BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_dma_done_cb ; 
 scalar_t__ bio_end_sector (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_meta_pool ; 
 int /*<<< orphan*/  blk_queue_split (struct request_queue*,struct bio**) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char,struct rsxx_bio_meta*,int,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_stats_start (struct rsxx_cardinfo*,struct bio*) ; 
 scalar_t__ get_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct rsxx_bio_meta* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct rsxx_bio_meta*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 scalar_t__ rsxx_dma_queue_bio (struct rsxx_cardinfo*,struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rsxx_bio_meta*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_qc_t rsxx_make_request(struct request_queue *q, struct bio *bio)
{
	struct rsxx_cardinfo *card = q->queuedata;
	struct rsxx_bio_meta *bio_meta;
	blk_status_t st = BLK_STS_IOERR;

	blk_queue_split(q, &bio);

	might_sleep();

	if (!card)
		goto req_err;

	if (bio_end_sector(bio) > get_capacity(card->gendisk))
		goto req_err;

	if (unlikely(card->halt))
		goto req_err;

	if (unlikely(card->dma_fault))
		goto req_err;

	if (bio->bi_iter.bi_size == 0) {
		dev_err(CARD_TO_DEV(card), "size zero BIO!\n");
		goto req_err;
	}

	bio_meta = kmem_cache_alloc(bio_meta_pool, GFP_KERNEL);
	if (!bio_meta) {
		st = BLK_STS_RESOURCE;
		goto req_err;
	}

	bio_meta->bio = bio;
	atomic_set(&bio_meta->error, 0);
	atomic_set(&bio_meta->pending_dmas, 0);
	bio_meta->start_time = jiffies;

	if (!unlikely(card->halt))
		disk_stats_start(card, bio);

	dev_dbg(CARD_TO_DEV(card), "BIO[%c]: meta: %p addr8: x%llx size: %d\n",
		 bio_data_dir(bio) ? 'W' : 'R', bio_meta,
		 (u64)bio->bi_iter.bi_sector << 9, bio->bi_iter.bi_size);

	st = rsxx_dma_queue_bio(card, bio, &bio_meta->pending_dmas,
				    bio_dma_done_cb, bio_meta);
	if (st)
		goto queue_err;

	return BLK_QC_T_NONE;

queue_err:
	kmem_cache_free(bio_meta_pool, bio_meta);
req_err:
	if (st)
		bio->bi_status = st;
	bio_endio(bio);
	return BLK_QC_T_NONE;
}