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
struct scatterlist {int dummy; } ;
struct msb_data {int* lba_to_pba_table; int cache_block_lba; int page_size; scalar_t__ cache; int /*<<< orphan*/  valid_cache_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct scatterlist*) ; 
 int /*<<< orphan*/  dbg_verbose (char*,int,int,int) ; 
 int /*<<< orphan*/  msb_cache_write (struct msb_data*,int,int,int,struct scatterlist*,int) ; 
 int msb_read_page (struct msb_data*,int,int,int /*<<< orphan*/ *,struct scatterlist*,int) ; 
 int /*<<< orphan*/  msb_sg_copy (struct scatterlist*,struct scatterlist*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (struct scatterlist*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (struct scatterlist*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msb_cache_read(struct msb_data *msb, int lba,
				int page, struct scatterlist *sg, int offset)
{
	int pba = msb->lba_to_pba_table[lba];
	struct scatterlist sg_tmp[10];
	int error = 0;

	if (lba == msb->cache_block_lba &&
			test_bit(page, &msb->valid_cache_bitmap)) {

		dbg_verbose("Read of LBA %d (pba %d) sector %d from cache",
							lba, pba, page);

		sg_init_table(sg_tmp, ARRAY_SIZE(sg_tmp));
		msb_sg_copy(sg, sg_tmp, ARRAY_SIZE(sg_tmp),
			offset, msb->page_size);
		sg_copy_from_buffer(sg_tmp, sg_nents(sg_tmp),
			msb->cache + msb->page_size * page,
							msb->page_size);
	} else {
		dbg_verbose("Read of LBA %d (pba %d) sector %d from device",
							lba, pba, page);

		error = msb_read_page(msb, pba, page, NULL, sg, offset);
		if (error)
			return error;

		msb_cache_write(msb, lba, page, true, sg, offset);
	}
	return error;
}