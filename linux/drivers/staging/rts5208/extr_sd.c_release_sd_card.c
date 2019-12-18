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
struct sd_info {int /*<<< orphan*/  raw_scr; int /*<<< orphan*/  raw_csd; scalar_t__ sd_erase_status; scalar_t__ sd_lock_status; } ;
struct rtsx_chip {scalar_t__ sd_int; scalar_t__ sd_io; int /*<<< orphan*/  card_wp; int /*<<< orphan*/  card_fail; int /*<<< orphan*/  card_ready; struct sd_info sd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_CARD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sd_power_off_card3v3 (struct rtsx_chip*) ; 

int release_sd_card(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;

	chip->card_ready &= ~SD_CARD;
	chip->card_fail &= ~SD_CARD;
	chip->card_wp &= ~SD_CARD;

	chip->sd_io = 0;
	chip->sd_int = 0;

#ifdef SUPPORT_SD_LOCK
	sd_card->sd_lock_status = 0;
	sd_card->sd_erase_status = 0;
#endif

	memset(sd_card->raw_csd, 0, 16);
	memset(sd_card->raw_scr, 0, 8);

	retval = sd_power_off_card3v3(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}