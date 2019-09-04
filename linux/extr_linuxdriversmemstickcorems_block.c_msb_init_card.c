#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; int /*<<< orphan*/  cylinders; } ;
struct msb_data {int caps; int read_only; int state; int page_size; int block_count; int pages_in_block; int block_size; TYPE_2__ geometry; int /*<<< orphan*/  block_buffer; struct ms_boot_page* boot_page; } ;
struct TYPE_7__ {int number_of_blocks; int page_size; int block_size; int transfer_supporting; int device_type; } ;
struct ms_boot_page {TYPE_3__ attr; } ;
struct memstick_host {int caps; } ;
struct TYPE_5__ {scalar_t__ class; } ;
struct memstick_dev {TYPE_1__ id; struct memstick_host* host; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  sec; int /*<<< orphan*/  head; int /*<<< orphan*/  cyl; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MEMSTICK_CAP_PAR4 ; 
 scalar_t__ MEMSTICK_CLASS_ROM ; 
 int PAGE_SIZE ; 
 TYPE_4__* chs_table ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 struct msb_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int msb_cache_init (struct msb_data*) ; 
 int msb_ftl_initialize (struct msb_data*) ; 
 int msb_ftl_scan (struct msb_data*) ; 
 int msb_read_bad_block_table (struct msb_data*,int) ; 
 int msb_read_boot_blocks (struct msb_data*) ; 
 int msb_reset (struct msb_data*,int) ; 
 int /*<<< orphan*/  msb_switch_to_parallel (struct msb_data*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int msb_init_card(struct memstick_dev *card)
{
	struct msb_data *msb = memstick_get_drvdata(card);
	struct memstick_host *host = card->host;
	struct ms_boot_page *boot_block;
	int error = 0, i, raw_size_in_megs;

	msb->caps = 0;

	if (card->id.class >= MEMSTICK_CLASS_ROM &&
				card->id.class <= MEMSTICK_CLASS_ROM)
		msb->read_only = true;

	msb->state = -1;
	error = msb_reset(msb, false);
	if (error)
		return error;

	/* Due to a bug in Jmicron driver written by Alex Dubov,
	 its serial mode barely works,
	 so we switch to parallel mode right away */
	if (host->caps & MEMSTICK_CAP_PAR4)
		msb_switch_to_parallel(msb);

	msb->page_size = sizeof(struct ms_boot_page);

	/* Read the boot page */
	error = msb_read_boot_blocks(msb);
	if (error)
		return -EIO;

	boot_block = &msb->boot_page[0];

	/* Save intersting attributes from boot page */
	msb->block_count = boot_block->attr.number_of_blocks;
	msb->page_size = boot_block->attr.page_size;

	msb->pages_in_block = boot_block->attr.block_size * 2;
	msb->block_size = msb->page_size * msb->pages_in_block;

	if (msb->page_size > PAGE_SIZE) {
		/* this isn't supported by linux at all, anyway*/
		dbg("device page %d size isn't supported", msb->page_size);
		return -EINVAL;
	}

	msb->block_buffer = kzalloc(msb->block_size, GFP_KERNEL);
	if (!msb->block_buffer)
		return -ENOMEM;

	raw_size_in_megs = (msb->block_size * msb->block_count) >> 20;

	for (i = 0; chs_table[i].size; i++) {

		if (chs_table[i].size != raw_size_in_megs)
			continue;

		msb->geometry.cylinders = chs_table[i].cyl;
		msb->geometry.heads = chs_table[i].head;
		msb->geometry.sectors = chs_table[i].sec;
		break;
	}

	if (boot_block->attr.transfer_supporting == 1)
		msb->caps |= MEMSTICK_CAP_PAR4;

	if (boot_block->attr.device_type & 0x03)
		msb->read_only = true;

	dbg("Total block count = %d", msb->block_count);
	dbg("Each block consists of %d pages", msb->pages_in_block);
	dbg("Page size = %d bytes", msb->page_size);
	dbg("Parallel mode supported: %d", !!(msb->caps & MEMSTICK_CAP_PAR4));
	dbg("Read only: %d", msb->read_only);

#if 0
	/* Now we can switch the interface */
	if (host->caps & msb->caps & MEMSTICK_CAP_PAR4)
		msb_switch_to_parallel(msb);
#endif

	error = msb_cache_init(msb);
	if (error)
		return error;

	error = msb_ftl_initialize(msb);
	if (error)
		return error;


	/* Read the bad block table */
	error = msb_read_bad_block_table(msb, 0);

	if (error && error != -ENOMEM) {
		dbg("failed to read bad block table from primary boot block, trying from backup");
		error = msb_read_bad_block_table(msb, 1);
	}

	if (error)
		return error;

	/* *drum roll* Scan the media */
	error = msb_ftl_scan(msb);
	if (error) {
		pr_err("Scan of media failed");
		return error;
	}

	return 0;

}