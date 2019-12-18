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
typedef  scalar_t__ u16 ;
struct scatterlist {int dummy; } ;
struct msb_data {scalar_t__* boot_block_locations; int page_size; int pages_in_block; scalar_t__ block_count; int /*<<< orphan*/  used_blocks_bitmap; struct ms_boot_page* boot_page; } ;
struct TYPE_3__ {int data_size; int start_addr; } ;
struct TYPE_4__ {TYPE_1__ disabled_block; } ;
struct ms_boot_page {TYPE_2__ entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MS_BLOCK_INVALID ; 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  dbg (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msb_mark_block_used (struct msb_data*,scalar_t__) ; 
 int msb_read_page (struct msb_data*,scalar_t__,int,int /*<<< orphan*/ *,struct scatterlist*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,scalar_t__*,int) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msb_read_bad_block_table(struct msb_data *msb, int block_nr)
{
	struct ms_boot_page *boot_block;
	struct scatterlist sg;
	u16 *buffer = NULL;
	int offset = 0;
	int i, error = 0;
	int data_size, data_offset, page, page_offset, size_to_read;
	u16 pba;

	BUG_ON(block_nr > 1);
	boot_block = &msb->boot_page[block_nr];
	pba = msb->boot_block_locations[block_nr];

	if (msb->boot_block_locations[block_nr] == MS_BLOCK_INVALID)
		return -EINVAL;

	data_size = boot_block->entry.disabled_block.data_size;
	data_offset = sizeof(struct ms_boot_page) +
			boot_block->entry.disabled_block.start_addr;
	if (!data_size)
		return 0;

	page = data_offset / msb->page_size;
	page_offset = data_offset % msb->page_size;
	size_to_read =
		DIV_ROUND_UP(data_size + page_offset, msb->page_size) *
			msb->page_size;

	dbg("reading bad block of boot block at pba %d, offset %d len %d",
		pba, data_offset, data_size);

	buffer = kzalloc(size_to_read, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	/* Read the buffer */
	sg_init_one(&sg, buffer, size_to_read);

	while (offset < size_to_read) {
		error = msb_read_page(msb, pba, page, NULL, &sg, offset);
		if (error)
			goto out;

		page++;
		offset += msb->page_size;

		if (page == msb->pages_in_block) {
			pr_err(
			"bad block table extends beyond the boot block");
			break;
		}
	}

	/* Process the bad block table */
	for (i = page_offset; i < data_size / sizeof(u16); i++) {

		u16 bad_block = be16_to_cpu(buffer[i]);

		if (bad_block >= msb->block_count) {
			dbg("bad block table contains invalid block %d",
								bad_block);
			continue;
		}

		if (test_bit(bad_block, msb->used_blocks_bitmap))  {
			dbg("duplicate bad block %d in the table",
				bad_block);
			continue;
		}

		dbg("block %d is marked as factory bad", bad_block);
		msb_mark_block_used(msb, bad_block);
	}
out:
	kfree(buffer);
	return error;
}