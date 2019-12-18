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
struct ms_info {int total_block; scalar_t__ ms_type; scalar_t__ check_ms_flow; } ;
struct rtsx_chip {struct ms_info ms_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_MSPRO (struct ms_info*) ; 
 int /*<<< orphan*/  MS_CARD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int enable_card_clock (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ms_info*,int /*<<< orphan*/ ,int) ; 
 int ms_build_l2p_tbl (struct rtsx_chip*,int) ; 
 int ms_set_init_para (struct rtsx_chip*) ; 
 int reset_ms (struct rtsx_chip*) ; 
 int reset_ms_pro (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int select_card (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

int reset_ms_card(struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &chip->ms_card;
	int seg_no = ms_card->total_block / 512 - 1;
	int retval;

	memset(ms_card, 0, sizeof(struct ms_info));

	retval = enable_card_clock(chip, MS_CARD);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = select_card(chip, MS_CARD);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	ms_card->ms_type = 0;

	retval = reset_ms_pro(chip);
	if (retval != STATUS_SUCCESS) {
		if (ms_card->check_ms_flow) {
			retval = reset_ms(chip);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;
		} else {
			return STATUS_FAIL;
		}
	}

	retval = ms_set_init_para(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	if (!CHK_MSPRO(ms_card)) {
		/* Build table for the last segment,
		 * to check if L2P table block exists, erasing it
		 */
		retval = ms_build_l2p_tbl(chip, seg_no);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;
	}

	dev_dbg(rtsx_dev(chip), "ms_card->ms_type = 0x%x\n", ms_card->ms_type);

	return STATUS_SUCCESS;
}