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
struct rtsx_chip {int int_reg; int card_ready; scalar_t__ sd_io; } ;

/* Variables and functions */
 int MS_CARD ; 
 int MS_EXIST ; 
 int /*<<< orphan*/  RTSX_BIPR ; 
 int SD_CARD ; 
 int SD_EXIST ; 
 int XD_CARD ; 
 int XD_EXIST ; 
 int /*<<< orphan*/  ms_cleanup_work (struct rtsx_chip*) ; 
 int /*<<< orphan*/  release_ms_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  release_sd_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  release_xd_card (struct rtsx_chip*) ; 
 int rtsx_readl (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_cleanup_work (struct rtsx_chip*) ; 
 int /*<<< orphan*/  xd_cleanup_work (struct rtsx_chip*) ; 

void rtsx_release_cards(struct rtsx_chip *chip)
{
	chip->int_reg = rtsx_readl(chip, RTSX_BIPR);

	if ((chip->card_ready & SD_CARD) || chip->sd_io) {
		if (chip->int_reg & SD_EXIST)
			sd_cleanup_work(chip);
		release_sd_card(chip);
	}

	if (chip->card_ready & XD_CARD) {
		if (chip->int_reg & XD_EXIST)
			xd_cleanup_work(chip);
		release_xd_card(chip);
	}

	if (chip->card_ready & MS_CARD) {
		if (chip->int_reg & MS_EXIST)
			ms_cleanup_work(chip);
		release_ms_card(chip);
	}
}