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
struct msb_data {int cache_block_lba; int page_size; int /*<<< orphan*/  valid_cache_bitmap; scalar_t__ cache; int /*<<< orphan*/  cache_flush_timer; scalar_t__ read_only; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct scatterlist*) ; 
 int EROFS ; 
 int MS_BLOCK_INVALID ; 
 int /*<<< orphan*/  cache_flush_timeout ; 
 int /*<<< orphan*/  dbg_verbose (char*,...) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int msb_cache_flush (struct msb_data*) ; 
 int /*<<< orphan*/  msb_sg_copy (struct scatterlist*,struct scatterlist*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (struct scatterlist*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (struct scatterlist*) ; 

__attribute__((used)) static int msb_cache_write(struct msb_data *msb, int lba,
	int page, bool add_to_cache_only, struct scatterlist *sg, int offset)
{
	int error;
	struct scatterlist sg_tmp[10];

	if (msb->read_only)
		return -EROFS;

	if (msb->cache_block_lba == MS_BLOCK_INVALID ||
						lba != msb->cache_block_lba)
		if (add_to_cache_only)
			return 0;

	/* If we need to write different block */
	if (msb->cache_block_lba != MS_BLOCK_INVALID &&
						lba != msb->cache_block_lba) {
		dbg_verbose("first flush the cache");
		error = msb_cache_flush(msb);
		if (error)
			return error;
	}

	if (msb->cache_block_lba  == MS_BLOCK_INVALID) {
		msb->cache_block_lba  = lba;
		mod_timer(&msb->cache_flush_timer,
			jiffies + msecs_to_jiffies(cache_flush_timeout));
	}

	dbg_verbose("Write of LBA %d page %d to cache ", lba, page);

	sg_init_table(sg_tmp, ARRAY_SIZE(sg_tmp));
	msb_sg_copy(sg, sg_tmp, ARRAY_SIZE(sg_tmp), offset, msb->page_size);

	sg_copy_to_buffer(sg_tmp, sg_nents(sg_tmp),
		msb->cache + page * msb->page_size, msb->page_size);

	set_bit(page, &msb->valid_cache_bitmap);
	return 0;
}