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
struct pmem_device {int data_offset; int /*<<< orphan*/  bb; void* virt_addr; } ;
struct page {int dummy; } ;
typedef  int sector_t ;
typedef  int phys_addr_t ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int is_bad_pmem (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  op_is_write (unsigned int) ; 
 int /*<<< orphan*/  pmem_clear_poison (struct pmem_device*,int,unsigned int) ; 
 int /*<<< orphan*/  read_pmem (struct page*,unsigned int,void*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_pmem (void*,struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static blk_status_t pmem_do_bvec(struct pmem_device *pmem, struct page *page,
			unsigned int len, unsigned int off, unsigned int op,
			sector_t sector)
{
	blk_status_t rc = BLK_STS_OK;
	bool bad_pmem = false;
	phys_addr_t pmem_off = sector * 512 + pmem->data_offset;
	void *pmem_addr = pmem->virt_addr + pmem_off;

	if (unlikely(is_bad_pmem(&pmem->bb, sector, len)))
		bad_pmem = true;

	if (!op_is_write(op)) {
		if (unlikely(bad_pmem))
			rc = BLK_STS_IOERR;
		else {
			rc = read_pmem(page, off, pmem_addr, len);
			flush_dcache_page(page);
		}
	} else {
		/*
		 * Note that we write the data both before and after
		 * clearing poison.  The write before clear poison
		 * handles situations where the latest written data is
		 * preserved and the clear poison operation simply marks
		 * the address range as valid without changing the data.
		 * In this case application software can assume that an
		 * interrupted write will either return the new good
		 * data or an error.
		 *
		 * However, if pmem_clear_poison() leaves the data in an
		 * indeterminate state we need to perform the write
		 * after clear poison.
		 */
		flush_dcache_page(page);
		write_pmem(pmem_addr, page, off, len);
		if (unlikely(bad_pmem)) {
			rc = pmem_clear_poison(pmem, pmem_off, len);
			write_pmem(pmem_addr, page, off, len);
		}
	}

	return rc;
}