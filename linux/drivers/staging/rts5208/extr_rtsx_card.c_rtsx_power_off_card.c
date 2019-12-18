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
struct rtsx_chip {int card_ready; scalar_t__ sd_io; } ;

/* Variables and functions */
 int MS_CARD ; 
 int SD_CARD ; 
 int XD_CARD ; 
 int /*<<< orphan*/  ms_cleanup_work (struct rtsx_chip*) ; 
 int /*<<< orphan*/  ms_power_off_card3v3 (struct rtsx_chip*) ; 
 int /*<<< orphan*/  sd_cleanup_work (struct rtsx_chip*) ; 
 int /*<<< orphan*/  sd_power_off_card3v3 (struct rtsx_chip*) ; 
 int /*<<< orphan*/  xd_cleanup_work (struct rtsx_chip*) ; 
 int /*<<< orphan*/  xd_power_off_card3v3 (struct rtsx_chip*) ; 

void rtsx_power_off_card(struct rtsx_chip *chip)
{
	if ((chip->card_ready & SD_CARD) || chip->sd_io) {
		sd_cleanup_work(chip);
		sd_power_off_card3v3(chip);
	}

	if (chip->card_ready & XD_CARD) {
		xd_cleanup_work(chip);
		xd_power_off_card3v3(chip);
	}

	if (chip->card_ready & MS_CARD) {
		ms_cleanup_work(chip);
		ms_power_off_card3v3(chip);
	}
}