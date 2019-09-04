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
typedef  int u8 ;
typedef  size_t u16 ;
struct msb_data {size_t block_count; size_t* boot_block_locations; size_t* lba_to_pba_table; int /*<<< orphan*/  used_blocks_bitmap; } ;
struct ms_extra_data_register {int management_flag; int overwrite_flag; int /*<<< orphan*/  logical_address; } ;
typedef  int /*<<< orphan*/  extra ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MEMSTICK_MANAGEMENT_ATFLG ; 
 int MEMSTICK_MANAGEMENT_FLAG_NORMAL ; 
 int MEMSTICK_OVERWRITE_BKST ; 
 int MEMSTICK_OVERWRITE_UDST ; 
 size_t MS_BLOCK_INVALID ; 
 size_t be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  dbg_verbose (char*,size_t,...) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ms_extra_data_register*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msb_erase_block (struct msb_data*,size_t) ; 
 scalar_t__ msb_get_zone_from_lba (size_t) ; 
 scalar_t__ msb_get_zone_from_pba (size_t) ; 
 int /*<<< orphan*/  msb_mark_block_used (struct msb_data*,size_t) ; 
 int msb_read_oob (struct msb_data*,size_t,int /*<<< orphan*/ ,struct ms_extra_data_register*) ; 
 int /*<<< orphan*/  pr_err (char*,int,size_t) ; 
 int /*<<< orphan*/  pr_notice (char*,size_t,...) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msb_ftl_scan(struct msb_data *msb)
{
	u16 pba, lba, other_block;
	u8 overwrite_flag, management_flag, other_overwrite_flag;
	int error;
	struct ms_extra_data_register extra;
	u8 *overwrite_flags = kzalloc(msb->block_count, GFP_KERNEL);

	if (!overwrite_flags)
		return -ENOMEM;

	dbg("Start of media scanning");
	for (pba = 0; pba < msb->block_count; pba++) {

		if (pba == msb->boot_block_locations[0] ||
			pba == msb->boot_block_locations[1]) {
			dbg_verbose("pba %05d -> [boot block]", pba);
			msb_mark_block_used(msb, pba);
			continue;
		}

		if (test_bit(pba, msb->used_blocks_bitmap)) {
			dbg_verbose("pba %05d -> [factory bad]", pba);
			continue;
		}

		memset(&extra, 0, sizeof(extra));
		error = msb_read_oob(msb, pba, 0, &extra);

		/* can't trust the page if we can't read the oob */
		if (error == -EBADMSG) {
			pr_notice(
			"oob of pba %d damaged, will try to erase it", pba);
			msb_mark_block_used(msb, pba);
			msb_erase_block(msb, pba);
			continue;
		} else if (error) {
			pr_err("unknown error %d on read of oob of pba %d - aborting",
				error, pba);

			kfree(overwrite_flags);
			return error;
		}

		lba = be16_to_cpu(extra.logical_address);
		management_flag = extra.management_flag;
		overwrite_flag = extra.overwrite_flag;
		overwrite_flags[pba] = overwrite_flag;

		/* Skip bad blocks */
		if (!(overwrite_flag & MEMSTICK_OVERWRITE_BKST)) {
			dbg("pba %05d -> [BAD]", pba);
			msb_mark_block_used(msb, pba);
			continue;
		}

		/* Skip system/drm blocks */
		if ((management_flag & MEMSTICK_MANAGEMENT_FLAG_NORMAL) !=
			MEMSTICK_MANAGEMENT_FLAG_NORMAL) {
			dbg("pba %05d -> [reserved management flag %02x]",
							pba, management_flag);
			msb_mark_block_used(msb, pba);
			continue;
		}

		/* Erase temporary tables */
		if (!(management_flag & MEMSTICK_MANAGEMENT_ATFLG)) {
			dbg("pba %05d -> [temp table] - will erase", pba);

			msb_mark_block_used(msb, pba);
			msb_erase_block(msb, pba);
			continue;
		}

		if (lba == MS_BLOCK_INVALID) {
			dbg_verbose("pba %05d -> [free]", pba);
			continue;
		}

		msb_mark_block_used(msb, pba);

		/* Block has LBA not according to zoning*/
		if (msb_get_zone_from_lba(lba) != msb_get_zone_from_pba(pba)) {
			pr_notice("pba %05d -> [bad lba %05d] - will erase",
								pba, lba);
			msb_erase_block(msb, pba);
			continue;
		}

		/* No collisions - great */
		if (msb->lba_to_pba_table[lba] == MS_BLOCK_INVALID) {
			dbg_verbose("pba %05d -> [lba %05d]", pba, lba);
			msb->lba_to_pba_table[lba] = pba;
			continue;
		}

		other_block = msb->lba_to_pba_table[lba];
		other_overwrite_flag = overwrite_flags[other_block];

		pr_notice("Collision between pba %d and pba %d",
			pba, other_block);

		if (!(overwrite_flag & MEMSTICK_OVERWRITE_UDST)) {
			pr_notice("pba %d is marked as stable, use it", pba);
			msb_erase_block(msb, other_block);
			msb->lba_to_pba_table[lba] = pba;
			continue;
		}

		if (!(other_overwrite_flag & MEMSTICK_OVERWRITE_UDST)) {
			pr_notice("pba %d is marked as stable, use it",
								other_block);
			msb_erase_block(msb, pba);
			continue;
		}

		pr_notice("collision between blocks %d and %d, without stable flag set on both, erasing pba %d",
				pba, other_block, other_block);

		msb_erase_block(msb, other_block);
		msb->lba_to_pba_table[lba] = pba;
	}

	dbg("End of media scanning");
	kfree(overwrite_flags);
	return 0;
}