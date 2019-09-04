#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct scatterlist {scalar_t__ length; } ;
struct TYPE_5__ {int management_flag; int overwrite_flag; void* logical_address; } ;
struct TYPE_4__ {void* block_address; scalar_t__ page_address; int /*<<< orphan*/  cp; } ;
struct TYPE_6__ {TYPE_2__ extra_data; TYPE_1__ param; } ;
struct msb_data {scalar_t__ page_size; scalar_t__ block_count; scalar_t__ logical_block_count; scalar_t__* boot_block_locations; int current_sg_offset; int /*<<< orphan*/  erased_blocks_bitmap; scalar_t__ current_page; struct scatterlist* current_sg; TYPE_3__ regs; scalar_t__ read_only; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EROFS ; 
 int /*<<< orphan*/  MEMSTICK_CP_BLOCK ; 
 scalar_t__ MS_BLOCK_INVALID ; 
 void* cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  h_msb_write_block ; 
 int msb_erase_block (struct msb_data*,scalar_t__) ; 
 scalar_t__ msb_get_zone_from_lba (scalar_t__) ; 
 scalar_t__ msb_get_zone_from_pba (scalar_t__) ; 
 scalar_t__ msb_reset (struct msb_data*,int) ; 
 int msb_run_state_machine (struct msb_data*,int /*<<< orphan*/ ) ; 
 int msb_verify_block (struct msb_data*,scalar_t__,struct scatterlist*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ verify_writes ; 

__attribute__((used)) static int msb_write_block(struct msb_data *msb,
			u16 pba, u32 lba, struct scatterlist *sg, int offset)
{
	int error, current_try = 1;
	BUG_ON(sg->length < msb->page_size);

	if (msb->read_only)
		return -EROFS;

	if (pba == MS_BLOCK_INVALID) {
		pr_err(
			"BUG: write: attempt to write MS_BLOCK_INVALID block");
		return -EINVAL;
	}

	if (pba >= msb->block_count || lba >= msb->logical_block_count) {
		pr_err(
		"BUG: write: attempt to write beyond the end of device");
		return -EINVAL;
	}

	if (msb_get_zone_from_lba(lba) != msb_get_zone_from_pba(pba)) {
		pr_err("BUG: write: lba zone mismatch");
		return -EINVAL;
	}

	if (pba == msb->boot_block_locations[0] ||
		pba == msb->boot_block_locations[1]) {
		pr_err("BUG: write: attempt to write to boot blocks!");
		return -EINVAL;
	}

	while (1) {

		if (msb->read_only)
			return -EROFS;

		msb->regs.param.cp = MEMSTICK_CP_BLOCK;
		msb->regs.param.page_address = 0;
		msb->regs.param.block_address = cpu_to_be16(pba);

		msb->regs.extra_data.management_flag = 0xFF;
		msb->regs.extra_data.overwrite_flag = 0xF8;
		msb->regs.extra_data.logical_address = cpu_to_be16(lba);

		msb->current_sg = sg;
		msb->current_sg_offset = offset;
		msb->current_page = 0;

		error = msb_run_state_machine(msb, h_msb_write_block);

		/* Sector we just wrote to is assumed erased since its pba
			was erased. If it wasn't erased, write will succeed
			and will just clear the bits that were set in the block
			thus test that what we have written,
			matches what we expect.
			We do trust the blocks that we erased */
		if (!error && (verify_writes ||
				!test_bit(pba, msb->erased_blocks_bitmap)))
			error = msb_verify_block(msb, pba, sg, offset);

		if (!error)
			break;

		if (current_try > 1 || msb_reset(msb, true))
			break;

		pr_err("write failed, trying to erase the pba %d", pba);
		error = msb_erase_block(msb, pba);
		if (error)
			break;

		current_try++;
	}
	return error;
}