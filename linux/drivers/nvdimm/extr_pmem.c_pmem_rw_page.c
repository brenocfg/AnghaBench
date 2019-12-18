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
struct pmem_device {int dummy; } ;
struct page {int dummy; } ;
struct block_device {TYPE_1__* bd_queue; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_2__ {struct pmem_device* queuedata; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int blk_status_to_errno (scalar_t__) ; 
 int hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  op_is_write (unsigned int) ; 
 int /*<<< orphan*/  page_endio (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pmem_do_bvec (struct pmem_device*,struct page*,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmem_rw_page(struct block_device *bdev, sector_t sector,
		       struct page *page, unsigned int op)
{
	struct pmem_device *pmem = bdev->bd_queue->queuedata;
	blk_status_t rc;

	rc = pmem_do_bvec(pmem, page, hpage_nr_pages(page) * PAGE_SIZE,
			  0, op, sector);

	/*
	 * The ->rw_page interface is subtle and tricky.  The core
	 * retries on any error, so we can only invoke page_endio() in
	 * the successful completion case.  Otherwise, we'll see crashes
	 * caused by double completion.
	 */
	if (rc == 0)
		page_endio(page, op_is_write(op), 0);

	return blk_status_to_errno(rc);
}