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
struct log_writes_c {size_t sectorsize; TYPE_2__* logdev; } ;
struct TYPE_3__ {scalar_t__ bi_sector; scalar_t__ bi_size; } ;
struct bio {struct log_writes_c* bi_private; int /*<<< orphan*/  bi_end_io; TYPE_1__ bi_iter; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 scalar_t__ WRITE_LOG_SUPER_SECTOR ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 size_t bio_add_page (struct bio*,struct page*,size_t,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  log_end_io ; 
 int /*<<< orphan*/  log_end_super ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  put_io_block (struct log_writes_c*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static int write_metadata(struct log_writes_c *lc, void *entry,
			  size_t entrylen, void *data, size_t datalen,
			  sector_t sector)
{
	struct bio *bio;
	struct page *page;
	void *ptr;
	size_t ret;

	bio = bio_alloc(GFP_KERNEL, 1);
	if (!bio) {
		DMERR("Couldn't alloc log bio");
		goto error;
	}
	bio->bi_iter.bi_size = 0;
	bio->bi_iter.bi_sector = sector;
	bio_set_dev(bio, lc->logdev->bdev);
	bio->bi_end_io = (sector == WRITE_LOG_SUPER_SECTOR) ?
			  log_end_super : log_end_io;
	bio->bi_private = lc;
	bio_set_op_attrs(bio, REQ_OP_WRITE, 0);

	page = alloc_page(GFP_KERNEL);
	if (!page) {
		DMERR("Couldn't alloc log page");
		bio_put(bio);
		goto error;
	}

	ptr = kmap_atomic(page);
	memcpy(ptr, entry, entrylen);
	if (datalen)
		memcpy(ptr + entrylen, data, datalen);
	memset(ptr + entrylen + datalen, 0,
	       lc->sectorsize - entrylen - datalen);
	kunmap_atomic(ptr);

	ret = bio_add_page(bio, page, lc->sectorsize, 0);
	if (ret != lc->sectorsize) {
		DMERR("Couldn't add page to the log block");
		goto error_bio;
	}
	submit_bio(bio);
	return 0;
error_bio:
	bio_put(bio);
	__free_page(page);
error:
	put_io_block(lc);
	return -1;
}