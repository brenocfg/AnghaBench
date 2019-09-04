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
typedef  size_t u16 ;
struct scatterlist {int dummy; } ;
struct msb_data {size_t* lba_to_pba_table; int read_only; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EIO ; 
 int MEMSTICK_OVERWRITE_UDST ; 
 size_t MS_BLOCK_INVALID ; 
 int /*<<< orphan*/  dbg_verbose (char*,...) ; 
 int /*<<< orphan*/  msb_erase_block (struct msb_data*,size_t) ; 
 size_t msb_get_free_block (struct msb_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msb_get_zone_from_lba (size_t) ; 
 int /*<<< orphan*/  msb_mark_bad (struct msb_data*,size_t) ; 
 int /*<<< orphan*/  msb_set_overwrite_flag (struct msb_data*,size_t,int /*<<< orphan*/ ,int) ; 
 int msb_write_block (struct msb_data*,size_t,size_t,struct scatterlist*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int msb_update_block(struct msb_data *msb, u16 lba,
	struct scatterlist *sg, int offset)
{
	u16 pba, new_pba;
	int error, try;

	pba = msb->lba_to_pba_table[lba];
	dbg_verbose("start of a block update at lba  %d, pba %d", lba, pba);

	if (pba != MS_BLOCK_INVALID) {
		dbg_verbose("setting the update flag on the block");
		msb_set_overwrite_flag(msb, pba, 0,
				0xFF & ~MEMSTICK_OVERWRITE_UDST);
	}

	for (try = 0; try < 3; try++) {
		new_pba = msb_get_free_block(msb,
			msb_get_zone_from_lba(lba));

		if (new_pba == MS_BLOCK_INVALID) {
			error = -EIO;
			goto out;
		}

		dbg_verbose("block update: writing updated block to the pba %d",
								new_pba);
		error = msb_write_block(msb, new_pba, lba, sg, offset);
		if (error == -EBADMSG) {
			msb_mark_bad(msb, new_pba);
			continue;
		}

		if (error)
			goto out;

		dbg_verbose("block update: erasing the old block");
		msb_erase_block(msb, pba);
		msb->lba_to_pba_table[lba] = new_pba;
		return 0;
	}
out:
	if (error) {
		pr_err("block update error after %d tries,  switching to r/o mode", try);
		msb->read_only = true;
	}
	return error;
}