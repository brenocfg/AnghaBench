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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ms_info {scalar_t__ page_off; } ;
struct rtsx_chip {struct ms_info ms_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_CLR_BAD_BLOCK_FLG (struct ms_info*) ; 
 scalar_t__ MS_TST_BAD_BLOCK_FLG (struct ms_info*) ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int ms_copy_page (struct rtsx_chip*,int,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int ms_erase_block (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  ms_set_bad_block (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  ms_set_l2p_tbl (struct rtsx_chip*,int,int,int) ; 
 int /*<<< orphan*/  ms_set_unused_block (struct rtsx_chip*,int) ; 
 int* ms_start_idx ; 

__attribute__((used)) static int ms_finish_write(struct rtsx_chip *chip, u16 old_blk, u16 new_blk,
			   u16 log_blk, u8 page_off)
{
	struct ms_info *ms_card = &chip->ms_card;
	int retval, seg_no;

	retval = ms_copy_page(chip, old_blk, new_blk, log_blk,
			      page_off, ms_card->page_off + 1);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	seg_no = old_blk >> 9;

	if (MS_TST_BAD_BLOCK_FLG(ms_card)) {
		MS_CLR_BAD_BLOCK_FLG(ms_card);
		ms_set_bad_block(chip, old_blk);
	} else {
		retval = ms_erase_block(chip, old_blk);
		if (retval == STATUS_SUCCESS)
			ms_set_unused_block(chip, old_blk);
	}

	ms_set_l2p_tbl(chip, seg_no, log_blk - ms_start_idx[seg_no], new_blk);

	return STATUS_SUCCESS;
}