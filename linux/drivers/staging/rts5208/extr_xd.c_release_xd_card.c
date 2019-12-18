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
struct xd_info {TYPE_1__ delay_write; } ;
struct rtsx_chip {int /*<<< orphan*/  card_wp; int /*<<< orphan*/  card_fail; int /*<<< orphan*/  card_ready; struct xd_info xd_card; } ;

/* Variables and functions */
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  XD_CARD ; 
 int /*<<< orphan*/  xd_free_l2p_tbl (struct rtsx_chip*) ; 
 int xd_power_off_card3v3 (struct rtsx_chip*) ; 

int release_xd_card(struct rtsx_chip *chip)
{
	struct xd_info *xd_card = &chip->xd_card;
	int retval;

	chip->card_ready &= ~XD_CARD;
	chip->card_fail &= ~XD_CARD;
	chip->card_wp &= ~XD_CARD;

	xd_card->delay_write.delay_write_flag = 0;

	xd_free_l2p_tbl(chip);

	retval = xd_power_off_card3v3(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}