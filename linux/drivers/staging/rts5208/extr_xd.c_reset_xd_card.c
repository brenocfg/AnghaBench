#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ delay_write_flag; } ;
struct xd_info {int cis_block; TYPE_1__ delay_write; scalar_t__ zone_cnt; scalar_t__ capacity; scalar_t__ addr_cycle; scalar_t__ page_off; scalar_t__ block_shift; } ;
struct rtsx_chip {struct xd_info xd_card; } ;

/* Variables and functions */
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  XD_CARD ; 
 int enable_card_clock (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xd_info*,int /*<<< orphan*/ ,int) ; 
 int reset_xd (struct rtsx_chip*) ; 
 int xd_init_l2p_tbl (struct rtsx_chip*) ; 

int reset_xd_card(struct rtsx_chip *chip)
{
	struct xd_info *xd_card = &chip->xd_card;
	int retval;

	memset(xd_card, 0, sizeof(struct xd_info));

	xd_card->block_shift = 0;
	xd_card->page_off = 0;
	xd_card->addr_cycle = 0;
	xd_card->capacity = 0;
	xd_card->zone_cnt = 0;
	xd_card->cis_block = 0xFFFF;
	xd_card->delay_write.delay_write_flag = 0;

	retval = enable_card_clock(chip, XD_CARD);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = reset_xd(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = xd_init_l2p_tbl(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}