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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  invalid_io; } ;
struct zram {TYPE_2__ stats; } ;
struct page {int dummy; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct bio_vec {scalar_t__ bv_offset; int /*<<< orphan*/  bv_len; struct page* bv_page; } ;
typedef  int sector_t ;
struct TYPE_3__ {struct zram* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int SECTORS_PER_PAGE ; 
 int SECTORS_PER_PAGE_SHIFT ; 
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_is_write (unsigned int) ; 
 int /*<<< orphan*/  page_endio (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  valid_io_request (struct zram*,int,int /*<<< orphan*/ ) ; 
 int zram_bvec_rw (struct zram*,struct bio_vec*,int,int,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zram_rw_page(struct block_device *bdev, sector_t sector,
		       struct page *page, unsigned int op)
{
	int offset, ret;
	u32 index;
	struct zram *zram;
	struct bio_vec bv;

	if (PageTransHuge(page))
		return -ENOTSUPP;
	zram = bdev->bd_disk->private_data;

	if (!valid_io_request(zram, sector, PAGE_SIZE)) {
		atomic64_inc(&zram->stats.invalid_io);
		ret = -EINVAL;
		goto out;
	}

	index = sector >> SECTORS_PER_PAGE_SHIFT;
	offset = (sector & (SECTORS_PER_PAGE - 1)) << SECTOR_SHIFT;

	bv.bv_page = page;
	bv.bv_len = PAGE_SIZE;
	bv.bv_offset = 0;

	ret = zram_bvec_rw(zram, &bv, index, offset, op, NULL);
out:
	/*
	 * If I/O fails, just return error(ie, non-zero) without
	 * calling page_endio.
	 * It causes resubmit the I/O with bio request by upper functions
	 * of rw_page(e.g., swap_readpage, __swap_writepage) and
	 * bio->bi_end_io does things to handle the error
	 * (e.g., SetPageError, set_page_dirty and extra works).
	 */
	if (unlikely(ret < 0))
		return ret;

	switch (ret) {
	case 0:
		page_endio(page, op_is_write(op), 0);
		break;
	case 1:
		ret = 0;
		break;
	default:
		WARN_ON(1);
	}
	return ret;
}