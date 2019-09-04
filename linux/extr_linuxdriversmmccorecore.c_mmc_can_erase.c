#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cmdclass; } ;
struct mmc_card {int quirks; scalar_t__ erase_size; TYPE_2__ csd; TYPE_1__* host; } ;
struct TYPE_3__ {int caps; } ;

/* Variables and functions */
 int CCC_ERASE ; 
 int MMC_CAP_ERASE ; 
 int MMC_QUIRK_ERASE_BROKEN ; 

int mmc_can_erase(struct mmc_card *card)
{
	if ((card->host->caps & MMC_CAP_ERASE) &&
	    (card->csd.cmdclass & CCC_ERASE) && card->erase_size &&
	    !(card->quirks & MMC_QUIRK_ERASE_BROKEN))
		return 1;
	return 0;
}