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
struct TYPE_2__ {scalar_t__ power_off_notification; } ;
struct mmc_card {TYPE_1__ ext_csd; } ;

/* Variables and functions */
 scalar_t__ EXT_CSD_POWER_ON ; 
 scalar_t__ mmc_card_mmc (struct mmc_card const*) ; 

__attribute__((used)) static int mmc_can_poweroff_notify(const struct mmc_card *card)
{
	return card &&
		mmc_card_mmc(card) &&
		(card->ext_csd.power_off_notification == EXT_CSD_POWER_ON);
}