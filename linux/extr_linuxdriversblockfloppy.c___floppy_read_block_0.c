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
struct rb0_cbdata {int drive; int /*<<< orphan*/  complete; } ;
struct page {int dummy; } ;
struct block_device {size_t bd_block_size; } ;
struct bio_vec {int dummy; } ;
struct TYPE_2__ {scalar_t__ bi_sector; } ;
struct bio {int bi_flags; int /*<<< orphan*/  bi_end_io; struct rb0_cbdata* bi_private; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int BIO_QUIET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_add_page (struct bio*,struct page*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_init (struct bio*,struct bio_vec*,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,struct block_device*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floppy_rb0_cb ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_fd_request () ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __floppy_read_block_0(struct block_device *bdev, int drive)
{
	struct bio bio;
	struct bio_vec bio_vec;
	struct page *page;
	struct rb0_cbdata cbdata;
	size_t size;

	page = alloc_page(GFP_NOIO);
	if (!page) {
		process_fd_request();
		return -ENOMEM;
	}

	size = bdev->bd_block_size;
	if (!size)
		size = 1024;

	cbdata.drive = drive;

	bio_init(&bio, &bio_vec, 1);
	bio_set_dev(&bio, bdev);
	bio_add_page(&bio, page, size, 0);

	bio.bi_iter.bi_sector = 0;
	bio.bi_flags |= (1 << BIO_QUIET);
	bio.bi_private = &cbdata;
	bio.bi_end_io = floppy_rb0_cb;
	bio_set_op_attrs(&bio, REQ_OP_READ, 0);

	init_completion(&cbdata.complete);

	submit_bio(&bio);
	process_fd_request();

	wait_for_completion(&cbdata.complete);

	__free_page(page);

	return 0;
}