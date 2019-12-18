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
struct msb_data {size_t block_size; int cache_block_lba; int pages_in_block; scalar_t__ page_size; } ;
typedef  size_t off_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_verbose (char*,int) ; 
 int /*<<< orphan*/  msb_cache_discard (struct msb_data*) ; 
 int msb_cache_write (struct msb_data*,int,int,int,struct scatterlist*,size_t) ; 
 int msb_update_block (struct msb_data*,int,struct scatterlist*,size_t) ; 

__attribute__((used)) static int msb_do_write_request(struct msb_data *msb, int lba,
	int page, struct scatterlist *sg, size_t len, int *sucessfuly_written)
{
	int error = 0;
	off_t offset = 0;
	*sucessfuly_written = 0;

	while (offset < len) {
		if (page == 0 && len - offset >= msb->block_size) {

			if (msb->cache_block_lba == lba)
				msb_cache_discard(msb);

			dbg_verbose("Writing whole lba %d", lba);
			error = msb_update_block(msb, lba, sg, offset);
			if (error)
				return error;

			offset += msb->block_size;
			*sucessfuly_written += msb->block_size;
			lba++;
			continue;
		}

		error = msb_cache_write(msb, lba, page, false, sg, offset);
		if (error)
			return error;

		offset += msb->page_size;
		*sucessfuly_written += msb->page_size;

		page++;
		if (page == msb->pages_in_block) {
			page = 0;
			lba++;
		}
	}
	return 0;
}